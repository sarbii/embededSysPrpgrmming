cmd_/home/pi/ultra/sensor_module.ko := ld -EL -r  -T ./scripts/module-common.lds --build-id  -o /home/pi/ultra/sensor_module.ko /home/pi/ultra/sensor_module.o /home/pi/ultra/sensor_module.mod.o ;  true