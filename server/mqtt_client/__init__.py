from mqtt_client.client import start_mqtt
import threading

# mosquitto
# mosquitto_pub -t iot/dev -m "test msg"

def start_mqtt_thread():
    print("\033[0;33mStarting MQTT client.. \033[0m")
    thread = threading.Thread(target=start_mqtt, daemon=True)
    # thread.start()

