#ifndef KEY_HPP
#define KEY_HPP
#include <uORB/topics/key.h>
#include "/home/rs/px3/PX4-Autopilot/mavlink/include/mavlink/v2.0/key/mavlink_msg_key.h"
class MavlinkStreamKey : public MavlinkStream
{
public:
	static MavlinkStream *new_instance(Mavlink *mavlink) { return new MavlinkStreamKey(mavlink); }

	static constexpr const char *get_name_static() { return "KEY"; }
	static constexpr uint16_t get_id_static() { return MAVLINK_MSG_ID_ATTITUDE; }

	const char *get_name() const override { return get_name_static(); }
	uint16_t get_id() override { return get_id_static(); }

	unsigned get_size() override
	{
		return _att_sub.advertised() ? MAVLINK_MSG_ID_ATTITUDE_LEN + MAVLINK_NUM_NON_PAYLOAD_BYTES : 0;
	}

private:
	explicit MavlinkStreamKey(Mavlink *mavlink) : MavlinkStream(mavlink) {}

	uORB::Subscription _att_sub{ORB_ID(key)};
	//uORB::Subscription _angular_velocity_sub{ORB_ID(vehicle_angular_velocity)};

	bool send() override
	{
		key_s att;

		if (_att_sub.updated()) {
			while (true){
				//vehicle_angular_velocity_s angular_velocity{};
			//_angular_velocity_sub.copy(&angular_velocity);
			_att_sub.copy(&att);
			mavlink_key_t msg{};




			/*const matrix::Eulerf euler = matrix::Quatf(att.q);
			msg.time_boot_ms = att.timestamp / 1000;
			msg.roll = euler.phi();
			msg.pitch = euler.theta();
			msg.yaw = euler.psi();

			msg.rollspeed = angular_velocity.xyz[0];
			msg.pitchspeed = angular_velocity.xyz[1];
			msg.yawspeed = angular_velocity.xyz[2];
			mavlink_msg_attitude_send_struct(_mavlink->get_channel(), &msg);*/
			msg.timestamp=hrt_absolute_time();
			msg.i=att.i;
			strcpy(msg.k,att.k);
			mavlink_msg_key_send_struct(_mavlink->get_channel(),&msg);
			}

			return true;
		}

		return false;
	}
};
#endif
