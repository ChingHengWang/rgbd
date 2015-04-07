#ifndef RGBD_TRANSPORT_SERVER_H_
#define RGBD_TRANSPORT_SERVER_H_

#include "rgbd/Image.h"
#include "rgbd/shared_mem_server.h"

#include <ros/publisher.h>
#include <boost/thread.hpp>

namespace rgbd {

class Image;

class Server {

public:

    Server();

    virtual ~Server();

    void initialize(const std::string& name, RGBStorageType rgb_type = RGB_STORAGE_LOSSLESS, DepthStorageType depth_type = DEPTH_STORAGE_LOSSLESS);

    void send(const Image& image, bool threaded = false);

    const static int SERIALIZATION_VERSION;

protected:

    ros::Publisher pub_image_;
    RGBStorageType rgb_type_;
    DepthStorageType depth_type_;

    SharedMemServer shared_mem_server_;

    // Threaded sending
    boost::mutex send_mutex_shared_;
    boost::mutex send_mutex_topic_;
    boost::thread send_thread_;

    void sendImpl(const Image& image);

};

}

#endif
