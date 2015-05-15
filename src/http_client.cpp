#include "http_client.h"

namespace lftnet {

bool HttpClient::Send(HttpRequest& req) {
  TcpSocket socket;

  socket.Connect(req.Url().Host().c_str(), req.Url().Port());
  std::string request_string(req);
  socket.Write(request_string.c_str(), request_string.size());

  if(m_parser << socket) {
    m_responses.push_back(std::make_shared<lftnet::HttpResponse>(m_parser.Data()));
  }

  return m_responses.size() == 1;
};

std::shared_ptr<lftnet::HttpResponse> HttpClient::Latest() {
  return m_responses.front();
}

}
