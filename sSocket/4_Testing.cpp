// For Testing

// TCP - Socket
int main(int argc, char *argv[])
{
	int port = 27015;
	const char *server_addr = "127.0.0.1";
	char rcv_buff[1024];
	int sz_buff = 1024;
	SOCKET s;
	
	int sz_recv;
	
	cSocket::init();
    s = cSocket::tcpConnect(server_addr, port);
    do{
		sz_recv = cSocket::tcpRecv(s, rcv_buff, sz_buff);
		cout << "Recv: " << rcv_buff << endl;
	} while (rcv_buff == "end");
	std::string mex("Messaggio di Risposta");
	const char *send_mex = mex.c_str();
	cout << "Sending Message " << endl;
	cSocket::tcpSend(s, send_mex, sz_buff);
	cout << "Message Sent" << endl;
	cout << "Out of connect.." << endl;
    int a;
    cin >> a;
}
