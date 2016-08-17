# include <stdio.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <fcntl.h>

# define SRV_PORT 4444
# define CLNT_PORT 4445

int main ()
{
	int sock;
	int from_len;
	char buf[14];
	struct sockaddr_in clnt_addr, srv_addr;
/*
 * Initiate socket and fabricate socket options
 */
	sock = socket (AF_INET, SOCK_STREAM, 0);
	fcntl (sock, F_SETFL, O_NONBLOCK);
	clnt_addr.sin_family = AF_INET;
	clnt_addr.sin_addr.s_addr = htonl (INADDR_LOOPBACK);
	clnt_addr.sin_port = htons (CLNT_PORT);
	bind (sock, (struct sockaddr *)&clnt_addr, sizeof (clnt_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	srv_addr.sin_port = htons(SRV_PORT);
/*
 * Sending and processing message
 */
	while(1)
	{
		connect (sock, (struct sockaddr *)&srv_addr, 
							sizeof (srv_addr));
		if (sock == (-1))
		{
			perror("Socket creat error!\n");
			exit(1);
		}
		from_len = recv (sock, buf, 14, 0);
		send (sock, "I am your client!\n", 19, 0);
		write (1, buf, from_len);
		if (from_len == (-1))
		{
			printf ("Answer is missing!\n");
		}
		else break; 
	}
	close (sock);
	return 1;
}
