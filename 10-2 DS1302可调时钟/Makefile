CC = sdcc
CFLAGS = -mmcs51 --iram-size 512 --stack-auto --opt-code-size --model-small --code-size 8192  -DPRINTF_DISABLE_SUPPORT_FLOAT=1 -DPRINTF_DISABLE_SUPPORT_EXPONENTIAL=1 -DPRINTF_DISABLE_SUPPORT_LONG_LONG=1
TARGET = main.hex
SRCS = main.c printf.c delay.c DS1302.c key.c LCD1602.c
OBJS=$(SRCS:.c=.rel)
DEPS=$(SRCS:.c=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


-include $(DEPS)


%.d: %.c
	$(CC) $(CFLAGS) -MM $^ -o $@
	sed -i "s/\.o:/\.rel:/" $*.d

%.rel: %.c
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	rm -rf $(TARGET) *.rel *.d *.ihx *.asm *.lst *.rst *.sym *.lk *.hex

