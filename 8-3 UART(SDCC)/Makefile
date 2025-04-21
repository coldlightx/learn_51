CC = sdcc
CFLAGS = -mmcs51 --iram-size 512 --stack-auto --model-small --code-size 8192


BUILD_DIR = build
OBJECTS_DIR = $(BUILD_DIR)/objects
DEPS_DIR = $(BUILD_DIR)/deps
TARGET = $(BUILD_DIR)/main.hex
# SRCS = $(wildcard *.c)
SRCS = main.c delay.c UART.c serial_log.c
OBJS=$(addprefix $(OBJECTS_DIR)/,$(SRCS:.c=.rel))
DEPS=$(addprefix $(DEPS_DIR)/,$(SRCS:.c=.d))

$(shell mkdir -p $(OBJECTS_DIR))
$(shell mkdir -p $(DEPS_DIR))


all: $(TARGET)

clean:
	rm -rf build

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif


$(OBJECTS_DIR)/%.rel: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

$(DEPS_DIR)/%.d: %.c
	$(CC) $(CFLAGS) -MM $^ -o $@
	sed -i "s/\.o:/\.rel:/" $@