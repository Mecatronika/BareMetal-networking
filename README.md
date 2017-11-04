# libnet

A network stack implementation for BareMetal OS.

The goals of the project are this:

 - Provide a full stack implementation from ethernet to HTTP
 - Avoid dynamic buffer resizing, which reduces performance and security
 - Avoid arbitrary compile-time limits to allow scalability
 - Allow usage in both kernel and user space to increase reusability

