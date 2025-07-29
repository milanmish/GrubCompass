# Grub Compass

I'm building a compass that will point me and my friends to a random restaurant nearby.

We always have trouble deciding on a place to eat, so I'm building a device that does the job for us. After randomly picking a restaurant within a certain radius from our location, the compass needle will point in the direction of the unknown location. We then need to follow the compass until we reach the restaurant.

Hardware:
-  ESP32-DevKitC ([Datasheet](https://mm.digikey.com/Volume0/opasdata/d220001/medias/docus/754/ESP32-DevKitC_GSG_Ver1.4_2017.pdf))
- Adafruit PA1010D GPS ([Datasheet](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-mini-gps-pa1010d-module.pdf))
- Adafruit LIS3MDL Magnetometer ([Datasheet](https://mm.digikey.com/Volume0/opasdata/d220001/medias/docus/60/4479_Web.pdf))
- Continuous servo motor