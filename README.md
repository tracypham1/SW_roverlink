# SW_roverlink
Audio input and output testing on pi3

I used Pi3 Model B V1.2  and standard headset connected to a ADC USB adapter.

Notes: 
- pyaudio-record.py and usb-audio-input.py do not run with python3, only pyhton and python 2


1. Connecting USB I/O device
    - The pi audio input/output is default set to ...rpi_simple_soundcard, which i believe is the GPIO pins and/or moniter in which it is connected depending on what the media player/method of playing audio decides.
    - You will need to configure the default device to our USB so that we don't have to manually change it everytime we connect and disconnect it
3. Checking the status of the devices
    - "cat /proc/asound/modules" should display 0 snd_usb_audio aka (index)(name of device)
4. running the scripts
    - pyaudio-record.py r
        - requires pyaudio, wave libraries
        - records audio for a brief moment and outputs to 'output.wav' file
    - usb-audio-input.py requires numpy, pyaudio, analyse
 
 
 https://makersportal.com/blog/2018/8/23/recording-audio-on-the-raspberry-pi-with-python-and-a-usb-microphone
 - check the usb is connected
 - setting up pyauddio
 
 https://people.csail.mit.edu/hubert/pyaudio/docs/
 - the pyaudio documentation containing the original examle code
 - Input overflow error occured, resolved in 'usb-audio-input.py' 
 
 https://www.raspberrypi.org/forums/viewtopic.php?t=25173
 - another helpful link for setting up pyaudio aand streaming data
 
 https://code.google.com/archive/p/pygalaxy/wikis/SoundAnalyse.wiki
 - for import analyse
 - SoundAnalyse measures the loudness/pitch of the USB input in the example
 - Note: this converts the sound data into NumPy 16-bit mono array
 
 5. checking the audio that was recorded
 - because my usb audio did not have output, I used the headphone jack and forced the audio to be player thru it using "omxplayer"
 
 Common Issues/Solutions:
 - updating the system using "sudo apt-get update" or "sudo rpi-update"
 - IOError: [Errno -9996] Invalid input device means the audio device is not physically connected properly 
 - Input overflow error addressed in comments of 'usb-audio-input.py' 
 
 
