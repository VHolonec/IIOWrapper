#include <stdio.h>
#include <iio.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <string>


/* Global objects */
static struct iio_buffer *device_buffer = NULL;
static struct iio_channel *m_channel_accel_x = NULL;
static struct iio_context *m_network_context = NULL;
static struct iio_context * m_object_context = NULL;
static struct iio_device *m_dev = NULL;
static const char *dev_name = NULL;
static const char *channel_id = NULL;
static  int32_t *in_buf;

static struct iio_channel **channels;
static struct iio_context *ctx;

int main()
{

        /* Getting nwtowk iio device context */
        std::string uri = "ip:127.0.0.1";
       // m_network_context = iio_create_context_from_uri(uri.c_str());
       // m_object_context =  iio_context_clone(m_network_context);

        ctx= iio_create_local_context();

        m_dev = iio_context_find_device(ctx, "adis16505");
        dev_name = iio_device_get_name(m_dev);
        //m_channel_accel_x = iio_device_find_channel(m_dev, "accel_x", false);

        int channel_count = 0;
        printf("* Initializing IIO streaming channels:\n");

        for (int i = 0; i < iio_device_get_channels_count(m_dev); ++i) {
            struct iio_channel *chn = iio_device_get_channel(m_dev, i);
            if (iio_channel_is_scan_element(chn)) {
                printf("%s chn\n", iio_channel_get_id(chn));
                channel_count++;
            }
        }


        channels = (iio_channel **)calloc(channel_count, sizeof * channels );


        for (int i = 0; i < channel_count; ++i) {
            struct iio_channel *chn = iio_device_get_channel(m_dev, i);
            if (iio_channel_is_scan_element(chn))
                channels[i] = chn;
        }

        iio_channel_enable(channels[0]);
//        for (int i = 0; i < channel_count; ++i)
//        {
//                iio_channel_enable(channels[i]);
//                if (iio_channel_is_enabled(channels[i]) == true)
//                {
//                    printf("channel_enabled %d \n", i);
//                }
//        }


       // iio_channel_enable(m_channel_accel_x);
        //if (iio_channel_is_enabled(m_channel_accel_x)  ==true)
        {
        //    printf(" channel_enabled accel x \n");
        }


        uint32_t sample_size = 4;
        uint32_t buffer_length = 8;
         uint32_t buffer_mask = 1;

        struct iio_buffer *device_buffer =
                iio_device_create_buffer(m_dev, buffer_length, false);

        if (!device_buffer)
        {
             printf(" device_buffer err \n");
                return -1;
        }

        int count =0;

        while (true) {
                //device_buffer->mask = buffer_mask;
                ssize_t nbytes_rx = iio_buffer_refill(device_buffer);
                count++;
                if (nbytes_rx <= 0) {
                        printf("Error refilling buf %d\n", (int) nbytes_rx);
                        return -1;
                }

                in_buf = (int32_t*)malloc(sample_size * buffer_length);
                memset(in_buf, 0,sample_size * buffer_length*sizeof(int32_t));
                iio_channel_read(channels[0], device_buffer, in_buf, sample_size * buffer_length);
                printf("%d %d %d %d   count= %d \n", in_buf[0], in_buf[1] , in_buf[2], in_buf[3], count);
                free(in_buf);

        }
        return 0;
}
