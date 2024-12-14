import serial
import time
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
from comtypes import CLSCTX_ALL

ser = serial.Serial('COM7', 9600, timeout=1)  # Replace
time.sleep(2)

devices = AudioUtilities.GetSpeakers()
interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
volume = interface.QueryInterface(IAudioEndpointVolume)

while True:
    if ser.in_waiting > 0:
        command = ser.readline().decode('utf-8', errors='ignore').strip()

        if command == "UP":
            print("UP",min(volume.GetMasterVolumeLevelScalar() + 0.05, 1.0)*100)
            volume.SetMasterVolumeLevelScalar(min(volume.GetMasterVolumeLevelScalar() + 0.05, 1.0), None)
        elif command == "DOWN":
            print("DOWN",max(volume.GetMasterVolumeLevelScalar() - 0.05, 0.0)*100)
            volume.SetMasterVolumeLevelScalar(max(volume.GetMasterVolumeLevelScalar() - 0.05, 0.0), None)
        elif command == "MUTE":
            print("MUTE")
            volume.SetMute(not volume.GetMute(), None)
