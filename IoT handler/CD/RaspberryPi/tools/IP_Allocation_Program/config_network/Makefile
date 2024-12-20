TARGET=check_network
OBJS=check.o parse.o

all:$(TARGET)

$(TARGET): $(OBJS)
	gcc -o $@ $(OBJS)

clean:
	rm -rf $(OBJS) $(TARGET)

