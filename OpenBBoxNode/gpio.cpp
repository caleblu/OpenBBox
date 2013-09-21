#include "gpio.h"

GPIO::GPIO()
{
}


/****************************************************************
* gpio_export
****************************************************************/
int GPIO::gpio_export(unsigned int gpio)
{
   int fd, len;
   char buf[MAX_BUF];

   fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
   if (fd < 0) {
       perror("gpio/export");
       return fd;
   }

   len = snprintf(buf, sizeof(buf), "%d", gpio);
   write(fd, buf, len);
   close(fd);

   return 0;
}

/****************************************************************
* gpio_unexport
****************************************************************/
int GPIO::gpio_unexport(unsigned int gpio)
{
   int fd, len;
   char buf[MAX_BUF];

   fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
   if (fd < 0) {
       perror("gpio/export");
       return fd;
   }

   len = snprintf(buf, sizeof(buf), "%d", gpio);
   write(fd, buf, len);
   close(fd);
   return 0;
}

/****************************************************************
* gpio_set_dir
****************************************************************/
int GPIO::gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
   int fd, len;
   char buf[MAX_BUF];

   len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

   fd = open(buf, O_WRONLY);
   if (fd < 0) {
       perror("gpio/direction");
       return fd;
   }

   if (out_flag)
       write(fd, "out", 4);
   else
       write(fd, "in", 3);

   close(fd);
   return 0;
}

/****************************************************************
* gpio_set_value
****************************************************************/
int GPIO::gpio_set_value(unsigned int gpio, unsigned int value)
{
   int fd, len;
   char buf[MAX_BUF];

   len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

   fd = open(buf, O_WRONLY);
   if (fd < 0) {
       perror(buf);
       return fd;
   }

   if (value)
       write(fd, "1", 2);
   else
       write(fd, "0", 2);

   close(fd);
   return 0;
}

/****************************************************************
* gpio_get_value
****************************************************************/
int GPIO::gpio_get_value(unsigned int gpio, unsigned int *value)
{
   int fd, len;
   char buf[MAX_BUF];
   char ch;

   len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

   fd = open(buf, O_RDONLY);
   if (fd < 0) {
       perror("gpio/get-value");
       return fd;
   }

   read(fd, &ch, 1);

   if (ch != '0') {
       *value = 1;
   } else {
       *value = 0;
   }

   close(fd);
   return 0;
}


/****************************************************************
* gpio_set_edge
****************************************************************/

int GPIO::gpio_set_edge(unsigned int gpio, char *edge)
{
   int fd, len;
   char buf[MAX_BUF];

   len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

   fd = open(buf, O_WRONLY);
   if (fd < 0) {
       perror("gpio/set-edge");
       return fd;
   }

   write(fd, edge, strlen(edge) + 1);
   close(fd);
   return 0;
}

/****************************************************************
* gpio_fd_open
****************************************************************/

int GPIO::gpio_fd_open(unsigned int gpio)
{
   int fd, len;
   char buf[MAX_BUF];

   len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

   fd = open(buf, O_RDONLY | O_NONBLOCK );
   if (fd < 0) {
       perror("gpio/fd_open");
   }
   return fd;
}

/****************************************************************
* gpio_fd_close
****************************************************************/

int GPIO::gpio_fd_close(int fd)
{
   return close(fd);
}
