COMPONENT_SRCDIRS := i2c_module/src sensor/ccs811/src sensor/hdc1080/src smartconfig wifi flash_nvs

COMPONENT_ADD_INCLUDEDIRS += i2c_module/inc sensor/ccs811/inc sensor/hdc1080/inc smartconfig wifi flash_nvs

# COMPONENT_ADD_LDFLAGS += $(COMPONENT_PATH)/airkiss/lib/libairkiss_aes.a \
#                          $(COMPONENT_PATH)/airkiss/lib/libairkiss_aes_log.a
