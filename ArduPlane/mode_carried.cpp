#include "mode.h"
#include "Plane.h"


bool ModeCarried::_enter()
{
    // SRV_Channels::set_output_scaled(SRV_Channel::k_aileron, 0);
    // SRV_Channels::set_output_scaled(SRV_Channel::k_elevator, 0);
    // plane.steering_control.steering = plane.steering_control.rudder = 0;
    plane.installed_released_x1 = 0;
    return true;
}

void ModeCarried::update()
{
    SRV_Channels::set_output_scaled(SRV_Channel::k_aileron, 0);
    SRV_Channels::set_output_scaled(SRV_Channel::k_elevator, 0);
    plane.steering_control.steering = plane.steering_control.rudder = 0;

    plane.nav_roll_cd = ahrs.roll_sensor;
    plane.nav_pitch_cd = ahrs.pitch_sensor;

    if (plane.installed_released_x1 == 8){
        if (!plane.arming.is_armed()) {
            plane.arming.arm(AP_Arming::Method::X1_installed, false);
        }
    }

    if (plane.installed_released_x1 >= 16){ 
        bool success_mode_change = plane.set_mode(plane.mode_auto, ModeReason::X1_released);
        if (success_mode_change) {
            gcs().send_text(MAV_SEVERITY_NOTICE, "Mode changed to AUTO");
        } else {
            gcs().send_text(MAV_SEVERITY_WARNING, "Failed to change mode to AUTO");
        }
    }
}