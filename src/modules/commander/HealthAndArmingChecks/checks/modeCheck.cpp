/****************************************************************************
 *
 *   Copyright (c) 2019-2020 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "modeCheck.hpp"

void ModeChecks::checkAndReport(const Context &context, Report &reporter)
{
	if (!context.isArmed()) {
		checkArmingRequirement(context, reporter);
	}

	// Failing mode requirements generally also clear the can_run bits which prevents mode switching and
	// might trigger a failsafe if already in that mode.

	if (!reporter.failsafeFlags().angular_velocity_valid && reporter.failsafeFlags().mode_req_angular_velocity != 0) {
		/* EVENT
		 * @description
		 * Make sure the gyroscope is providing valid data.
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_angular_velocity, health_component_t::system,
					    events::ID("check_modes_angular_velocity"),
					    events::Log::Critical, "Angular velocity not valid");
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_angular_velocity);
	}

	if (!reporter.failsafeFlags().attitude_valid && reporter.failsafeFlags().mode_req_attitude != 0) {
		/* EVENT
		 * @description
		 * Wait until the estimator initialized
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_attitude, health_component_t::system,
					    events::ID("check_modes_attitude"),
					    events::Log::Critical, "No valid attitude estimate");
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_attitude);
	}

	if (!reporter.failsafeFlags().local_position_valid && reporter.failsafeFlags().mode_req_local_position != 0) {
		/* EVENT
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_local_position, health_component_t::system,
					    events::ID("check_modes_local_pos"),
					    events::Log::Error, "No valid local position estimate");
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_local_position);
	}

	if (!reporter.failsafeFlags().global_position_valid && reporter.failsafeFlags().mode_req_global_position != 0) {
		/* EVENT
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_global_position, health_component_t::system,
					    events::ID("check_modes_global_pos"),
					    events::Log::Error, "No valid global position estimate");
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_global_position);
	}

	if (!reporter.failsafeFlags().local_altitude_valid && reporter.failsafeFlags().mode_req_local_alt != 0) {
		/* EVENT
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_local_alt, health_component_t::system,
					    events::ID("check_modes_local_alt"),
					    events::Log::Critical, "No valid altitude estimate");
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_local_alt);
	}

	if (!reporter.failsafeFlags().auto_mission_available && reporter.failsafeFlags().mode_req_mission != 0) {
		/* EVENT
		 * @description
		 * Upload a mission first.
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_mission, health_component_t::system,
					    events::ID("check_modes_mission"),
					    events::Log::Info, "No mission available");
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_mission);
	}

	if (reporter.failsafeFlags().offboard_control_signal_lost && reporter.failsafeFlags().mode_req_offboard_signal != 0) {
		/* EVENT
		 * @description
		 * The offboard component is not sending setpoints.
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_offboard_signal, health_component_t::system,
					    events::ID("check_modes_offboard_signal"),
					    events::Log::Error, "No offboard signal");
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_offboard_signal);
	}

	if (!reporter.failsafeFlags().home_position_valid && reporter.failsafeFlags().mode_req_home_position != 0) {
		/* EVENT
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_home_position, health_component_t::system,
					    events::ID("check_modes_home_position"),
					    events::Log::Info, "Home position not set");
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_home_position);
	}

	if (reporter.failsafeFlags().mode_req_other != 0) {
		// Here we expect there is already an event reported for the failing check (this is for external modes)
		reporter.clearCanRunBits((NavModes)reporter.failsafeFlags().mode_req_other);
	}
}

void ModeChecks::checkArmingRequirement(const Context &context, Report &reporter)
{
	if (reporter.failsafeFlags().mode_req_prevent_arming & (1u << context.status().nav_state)) {
		/* EVENT
		 * @description
		 * Switch to another mode first.
		 */
		reporter.armingCheckFailure((NavModes)reporter.failsafeFlags().mode_req_prevent_arming, health_component_t::system,
					    events::ID("check_modes_cannot_takeoff"),
					    events::Log::Info, "Mode not suitable for arming");
	}
}
