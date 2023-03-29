#include <stdio.h>
#include <iio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>


/* Global objects */
static struct iio_buffer *device_buffer = NULL;
static struct iio_channel *channel = NULL;
static struct iio_context *local_ctx = NULL;
static struct iio_device *dev = NULL;
static const char *dev_name = NULL;
static const char *channel_id = NULL;
static uint8_t *in_buf;


int main()
{

        /* Getting nwtowk iio device context */
        local_ctx = iio_create_network_context("127.0.0.1");
        //local_ctx = iio_create_context_from_uri("ip:127.0.0.1");
        dev = iio_context_find_device(local_ctx, "adis16505");

        channel = iio_device_find_channel(dev, "accel_x", false);

        //iio_channel_find_attr(channel, "raw");

        //if (iio_channel_find_attr(channel, "raw"))
        {
         //   double value = read_double_attr(channel, "raw");
        }
        long long value;
        int ret = iio_channel_attr_read_longlong(channel, "raw", &value);
        printf("value=%lld",value);

         ret = iio_channel_attr_read_longlong(channel, "raw", &value);
        printf("value=%lld",value);

        return 0;
}
