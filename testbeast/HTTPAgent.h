#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <boost/convert/lexical_cast.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class HTTPAgent
{
public:
	HTTPAgent(std::string host, std::string port);
	~HTTPAgent();
public:
    std::string AgentGet(std::string target);
    std::string AgentPost(std::string target, std::string body);
    std::string AgentDelete();
    std::string AgentUpdate();
private:
    std::string m_host = "39.106.175.239";
    std::string m_port = "8099";
    // The io_context is required for all I/O
    net::io_context m_ioc;

    // These objects perform our I/O
    tcp::resolver *m_resolver;//(ioc);
    beast::tcp_stream *m_stream;//(ioc);
};

