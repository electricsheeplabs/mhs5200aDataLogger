#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void waitFor (unsigned int secs) {
    unsigned int retTime = time(0) + secs;   // Get finishing time.
    while (time(0) < retTime);               // Loop until it arrives.
}


int main()
{
  //ask for filename..or get it piped over from bash?
  char str[1024];

   //printf( "Enter a file name (no extension):");
   scanf("%s", str);

//change the USB0 value to USB1, USB2, etc until your device is recognized!
char *portname = "/dev/ttyUSB0";
int fd;
int wlen;
FILE *fp;
unsigned char buf[80]="";
unsigned char buf1[15]="";
int rdlen;
//this is the serial command to which the MHS52000A responds by sending back frequency data (list of commands in a pdf in the repo)

char command[5] = ":r0e\n";

  while(1){
    fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        printf("Error opening %s: %s\n", portname, strerror(errno));
        return -1;
    }

    set_interface_attribs(fd, B57600);
    //set_mincount(fd, 0);
    fp = fopen(str, "a");

  //write command
    wlen = write(fd, command, sizeof(command));
    if (wlen != sizeof(command)) {
        printf("Error from write: %d, %d\n", wlen, errno);
    }
    tcdrain(fd);
    waitFor(1);

    //read response
        rdlen = read(fd, buf, sizeof(buf) - 1);
        if (rdlen > 0) {
                //get rid of command msg stuff
                int x=4;
                for(x;x<14;x++){
                  buf1[x-4]=buf[x];
                }
             fprintf(fp, "%s\n", buf1);
        }
        else if (rdlen < 0) {
              printf("Error from read: %d: %s\n", rdlen, strerror(errno));
        }

    fclose(fp);
    }

return(0);

}
