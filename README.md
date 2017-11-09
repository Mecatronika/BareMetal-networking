# netstack

A network stack implementation for BareMetal OS.

The goals of the project are this:

 - Provide a full stack implementation from ethernet to HTTP
 - Avoid dynamic buffer resizing, which reduces performance and security
 - Avoid arbitrary compile-time limits to allow scalability
 - Allow usage in both kernel and user space to increase reusability
 - Allow the integration of custom protocol implementations

Applications:

 - Kernel development
 - Virtual networking
 - High performance networking software

### Building

There are multiple build systems for the project.

You can build with the shell scripts:

```
./build.sh
./test.sh
```

With GNU Make:

```
make
make test
```

Or with CMake:

```
mkdir build
cd build
cmake ..
cmake --build .
ctest --verbose --output-on-failure
```

### Usage

Here's an example of how to setup a TCP/IPv6 stack:

```
#include <netstack/stack.h>

int main(void)
{
	struct netstack_stack stack;

	netstack_stack_init(&stack);

	int err = 0;
	err |= netstack_stack_push_ethernet(&stack);
	err |= netstack_stack_push_ipv6(&stack);
	err |= netstack_stack_push_tcp(&stack);
	if (err != 0)
	{
		fprintf(stderr, "Failed to construct network stack.\n");
		netstack_stack_done(&stack);
		return EXIT_FAILURE;
	}

	/* modify protocol parameters */

	/* application */

	netstack_stack_done(&stack);
}
```

Once the stack is setup, you might want to modify the protocol parameters.

For example, check the MAC address, IP address or port numbers.

You use the `netstack_mutator` structure to do this.

Here's an example:

```
int setup_ethernet(const void *mutator_data,
                   struct netstack_ethernet *ethernet)
{
	// See 'setup_stack' about the data
	// pointer.
	(void) mutator_data;

	const char dst_mac[] = "ff:aa:ee:bb:dd:cc";
	int err = netstack_ethernet_set_source(ethernet, src_mac, sizeof(src_mac) - 1);
	if (err != 0)
		return err;

	const char src_mac[] = "00:11:22:33:44:55";
	err = netstack_ethernet_set_destination(ethernet, dst_mac, sizeof(dst_mac) - 1);
	if (err != 0)
		return err;

	return 0;
}

int setup_ipv6(const void *mutator_data,
               struct netstack_ipv6 *ipv6)
{
	(void) mutator_data;

	(void) ipv6;

	return 0;
}

int setup_tcp(const void *mutator_data,
              struct netstack_tcp *tcp)
{
	(void) mutator_data;

	int err = netstack_tcp_set_source(tcp, "80", 2);
	if (err != 0)
		return err;

	err = netstack_tcp_set_destination(tcp, "80", 2);
	if (err != 0)
		return err;

	return 0;
}

int setup_stack(struct netstack_stack *stack)
{
	struct netstack_mutator mutator;

	netstack_mutator_init(&mutator);
	// The init function sets this to null,
	// but if you wanted to pass parameters
	// to the setup functions, you'd pass it
	// here.
	mutator.data = NULL;
	mutator.mutate_ethernet = setup_ethernet;
	mutator.mutate_ipv6 = setup_ipv6;
	mutator.mutate_tcp = setup_tcp;

	return netstack_stack_mutate(stack, &mutator);
}
```
