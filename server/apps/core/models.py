from django.db import models


class BaseModel(models.Model):
    is_active = models.BooleanField(default=True, verbose_name="ativo", null=False)
    class Meta:
        abstract = True 


class Address(BaseModel):
    street = models.CharField(null=False, blank=False, max_length=120)
    number = models.CharField(null=True, blank=True, max_length=5)
    neighborhood = models.CharField(null=True, blank=True, max_length=80)
    city = models.CharField(null=True, blank=True, max_length=80)
    state = models.CharField(null=True, blank=True, max_length=30)


class Institution(BaseModel):
    full_name = models.CharField(null=False, blank=False, max_length=120)
    acronym = models.CharField(null=False, blank=False, max_length=25)


class Campus(BaseModel):
    address = models.OneToOneField(Address)
    name = models.CharField(null=False, blank=False, max_length=80)