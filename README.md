# SW_roverlink
Audio input and output testing on pi3


Outline:
1. Setting up the Pi3 Model B V1.2
2. Connecting USB I/O device
    - The pi audio input/output is default set to ...rpi_simple_soundcard. which i believe is the GPIO pins and/or moniter in which it is connected depending on what the media player/method of playing audio decides.
    - for this we will need to configure the default to our USB so that we don't have to manually change it everytime we connect and disconnect it
3. Checking the status of the devices
    - "cat /proc/asound/modules" should display 0 snd_usb_audio aka (index)(name of device)
    - 
4. running the scripts
    - pyaudio-record.py requires pyaudio, wave libraries
    - usb-audio-input.py requires numpy, pyaudio, analyse
 
 Note: scripts do not run with python3, only pyhton and python 2
 
 Common Issues/Solutions:
 - updating the system using "sudo apt-get update"
 - IOError: [Errno -9996] Invalid input device means the audio device is not physically connected properly 
