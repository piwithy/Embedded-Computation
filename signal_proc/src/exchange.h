//
// Created by jezegoup on 23/11/2020.
//

#ifndef DFT_EXCHANGE_H
#define DFT_EXCHANGE_H

#include <zmq.hpp>

void sync_on_5556(zmq::context_t &context) {
    zmq::socket_t syncClient(context, zmq::socket_type::req);
    syncClient.connect("tcp://localhost:5556");
    zmq::message_t msg_sync(0);
    syncClient.send(msg_sync, zmq::send_flags::none);
    auto code = syncClient.recv(msg_sync, zmq::recv_flags::none);
}

zmq::socket_t create_subscriber_socket(zmq::context_t &context) {
    zmq::socket_t subscriber{context, zmq::socket_type::sub};
    subscriber.connect("tcp://localhost:5555");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);
    return subscriber;
}

std::vector<Complex> get_numpy_complex_stream(zmq::socket_t &subscriber) {
    zmq::message_t rmsg;
    auto  code = subscriber.recv(rmsg, zmq::recv_flags::none);
    const double *rdata = rmsg.data<double>();
    std::vector<double> real_part(N);
    real_part.assign(rdata, rdata + rmsg.size() / 8);

    zmq::message_t imsg;
    code = subscriber.recv(imsg, zmq::recv_flags::none);
    const double *idata = imsg.data<double>();
    std::vector<double> imag_part(N);
    imag_part.assign(idata, idata + imsg.size() / 8);

    using namespace std::complex_literals;
    std::vector<Complex> numpy_signal(real_part.size());
    for (std::size_t k = 0; k < numpy_signal.size(); k++) {
        numpy_signal[k] = real_part[k] + 1i * imag_part[k];
    }
    return numpy_signal;
}



#endif //DFT_EXCHANGE_H
