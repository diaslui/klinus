from django.db import models


class BaseModel(models.Model):
    is_active = models.BooleanField(default=True, verbose_name="ativo", null=False)
    class Meta:
        abstract = True 

    