#include <px4_platform_common/px4_config.h>
#include <px4_platform_common/tasks.h>
#include <px4_platform_common/posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <math.h>
//sss
#include <uORB/uORB.h>
#include <uORB/topics/key.h>

__EXPORT int key_main(int argc, char *argv[]);

 int key_main(int argc,char *argv[])
 {
	PX4_INFO("key generating!");
	struct key_s att;
	memset(&att,0,sizeof(att));
	orb_advert_t att_pub=orb_advertise(ORB_ID(key),&att);

	att.timestamp=hrt_absolute_time();
	strcpy(att.k,"there is the key!");
	att.i=2022;
	orb_publish(ORB_ID(key),att_pub,&att);

	sleep(100);
	return 0;
 }
