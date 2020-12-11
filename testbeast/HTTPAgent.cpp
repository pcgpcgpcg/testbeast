#include "HTTPAgent.h"

HTTPAgent::HTTPAgent(std::string host, std::string port){
	m_host = host;
	m_port = port;
	m_resolver = new tcp::resolver(m_ioc);
	
}

HTTPAgent::~HTTPAgent() {
	delete m_resolver;
	delete m_stream;
}

std::string HTTPAgent::AgentGet(std::string target) {
    std::string result = "";
    try
    {
        m_stream = new beast::tcp_stream(m_ioc);
        // Look up the domain name
        auto const results = m_resolver->resolve(m_host, m_port);
        // Make the connection on the IP address we get from a lookup
        m_stream->connect(results);
        // Set up an HTTP GET request message
        http::request<http::string_body> req{ http::verb::get, target, 1.1 };
        req.set(http::field::host, m_host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        // Send the HTTP request to the remote host
        http::write(*m_stream, req);
        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;
        // Declare a container to hold the response
        http::response<http::dynamic_body> res;
        // Receive the HTTP response
        http::read(*m_stream, buffer, res);
        // Write the message to standard out
        //res.body()
        res.result();
        res.result_int();

        std::stringstream ss;
        ss << res.result();
        result = ss.str();
        std::cout << res << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        m_stream->socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ ec };

        // If we get here then the connection is closed gracefully
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        //return EXIT_FAILURE;
    }

    return result;
}
std::string HTTPAgent::AgentPost(std::string target, std::string body) {
    std::string result = "";
    try
    {
        m_stream = new beast::tcp_stream(m_ioc);
        // Look up the domain name
        auto const results = m_resolver->resolve(m_host, m_port);
        // Make the connection on the IP address we get from a lookup
        m_stream->connect(results);
        // Set up an HTTP GET request message
        http::request<http::string_body> req{ http::verb::post, target, 1.1 };
        req.set(http::field::host, m_host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::content_length, boost::lexical_cast<std::string>(body.length()));
        req.set(http::field::body, body);
        // Send the HTTP request to the remote host
        http::write(*m_stream, req);
        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;
        // Declare a container to hold the response
        http::response<http::dynamic_body> res;
        // Receive the HTTP response
        http::read(*m_stream, buffer, res);
        // Write the message to standard out
        //res.body()
        res.result();
        res.result_int();

        std::stringstream ss;
        ss << res.result();
        result = ss.str();
        std::cout << res << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        m_stream->socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ ec };

        // If we get here then the connection is closed gracefully
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        //return EXIT_FAILURE;
    }

    return result;

}
std::string HTTPAgent::AgentDelete() {

}
std::string HTTPAgent::AgentUpdate() {

}