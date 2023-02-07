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
        dev = iio_context_get_device(local_ctx, 0);
        dev_name = iio_device_get_name(dev);
        channel = iio_device_get_channel(dev, 0);

        iio_channel_enable(channel);
        //if (iio_channel_is_enabled(channel))
        //        return -1;

        uint32_t sample_size = 3;
        uint32_t buffer_length = 1;

        struct iio_buffer *device_buffer =
                iio_device_create_buffer(dev, buffer_length, false);

        if (!device_buffer)
                return -1;

        while (true) {
               // ssize_t nbytes_rx = iio_buffer_refill(device_buffer);

               // if (nbytes_rx <= 0) {
               //         printf("Error refilling buf %d\n", (int) nbytes_rx);
               //         return -1;
               // }

                in_buf = (uint8_t*)malloc(sample_size * buffer_length);
                iio_channel_read(channel, device_buffer, in_buf, sample_size * buffer_length);
                printf("%" PRIi32 "\n", ((int32_t *)in_buf));
                free(in_buf);

        }
        return 0;
}
