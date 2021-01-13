#Header Header

int16 id
bool manual #1: manual. 0: automated
float32 thw
float32 alpha
float32 beta
float32 sensor2frontbumper
float32 sensor2rearbumper
int16 vel_gain
int16 vel_gain_low
int16 vel_gain_dec

#ego car
float32 x
float32 y
float32 u
float32 v
float32 yaw
float32 speed
float32 acceleration

#front car
float32 front_x
float32 front_y
float32 front_u
float32 front_v
float32 front_yaw
float32 front_speed
float32 front_acceleration
float32 front_distance

#rear car
float32 rear_x
float32 rear_y
float32 rear_u
float32 rear_v
float32 rear_yaw
float32 rear_speed
float32 rear_acceleration
float32 rear_distance

uint32 checksum