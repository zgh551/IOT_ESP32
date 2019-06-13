# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/components/include $(PROJECT_PATH)/components/i2c_module/inc $(PROJECT_PATH)/components/sensor/ccs811/inc $(PROJECT_PATH)/components/sensor/hdc1080/inc $(PROJECT_PATH)/components/smartconfig $(PROJECT_PATH)/components/wifi $(PROJECT_PATH)/components/flash_nvs $(PROJECT_PATH)/components/mqtt_esp_tcp $(PROJECT_PATH)/components/json_packet/inc
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/components -lcomponents
COMPONENT_LINKER_DEPS += 
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += components
COMPONENT_LDFRAGMENTS += 
component-components-build: 
