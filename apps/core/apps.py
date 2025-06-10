from django.apps import AppConfig
from mqtt_client import start_mqtt_thread


class CoreConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'apps.core'

    def ready(self):
        start_mqtt_thread()
