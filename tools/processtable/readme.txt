ptd - process table display

Simple utility to convert and display the process table memory dump from bochs into readable queues and tables.

Dump the process table into a text file:
1. bochs debugger command: x /64wx 0x80206000 (where 64 is actually 64*MAX_PROCESSES).
2. copy the memory dump into a text file, including the "<bogus..." text.
3. run "./ptd -da ptd.txt"

=======================
Previous Versions
=======================
Every time certain changes are made to the kernel, the ptd program changes with it, and if only some of the memory dumps have been saved without printing ptd's output to a file, then the dump files become useless. The most common cause of this is when the structure of the process table changes. If fields are moved, or new ones added, then any previous data is unreadable by the new format.

When I can think to do it, older versions are being archived. So far, this only really concerns me. Later on, hopefully the kernel will be stable, but if not then the ptd version will be important. Best of all, if any memory dumps are important, a copy of ptd's output should be saved (probably with all the options, ie use -da).



example bochs debugger memory dump (this shows the first two processes):

0x0000000080206000 <bogus+       0>:    0x00000001      0x00000081      0x00000000      0x00000000
0x0000000080206010 <bogus+      16>:    0x00000000      0x00000000      0x00001104      0x00000000
0x0000000080206020 <bogus+      32>:    0x00000000      0x00000258      0x7fffdffc      0x7ffffffc
0x0000000080206030 <bogus+      48>:    0x00000000      0x00000200      0x00004000      0xfffffff8
0x0000000080206040 <bogus+      64>:    0x00000001      0x00000001      0x00000000      0x00000000
0x0000000080206050 <bogus+      80>:    0x80206300      0x80206400      0x00000000      0x00000000
0x0000000080206060 <bogus+      96>:    0x00000000      0x00000000      0x00000000      0x00000000
0x0000000080206070 <bogus+     112>:    0x00000000      0x00000000      0x00000000      0x00000000
0x0000000080206080 <bogus+     128>:    0x00000000      0x00000000      0x00000000      0x00000000
0x0000000080206090 <bogus+     144>:    0x00000100      0x00000000      0x00000000      0x7ffffffc
0x00000000802060a0 <bogus+     160>:    0x00000010      0x00000000      0x00000000      0x00000000
0x00000000802060b0 <bogus+     176>:    0x00000000      0x00200000      0x8000490c      0x00000082
0x00000000802060c0 <bogus+     192>:    0x80103fa4      0x00000000      0x80207400      0x0000640c
0x00000000802060d0 <bogus+     208>:    0x80103fa4      0x80103fbc      0xffff807a      0x00080034
0x00000000802060e0 <bogus+     224>:    0x00000010      0x00000008      0x00000010      0x00000010
0x00000000802060f0 <bogus+     240>:    0x00000000      0x00000000      0x00000000      0x00670000
0x0000000080206100 <bogus+     256>:    0x00001001      0x00000081      0x00000000      0x00000000
0x0000000080206110 <bogus+     272>:    0x80206500      0x80206300      0x0f0f3105      0x00000001
0x0000000080206120 <bogus+     288>:    0x00000000      0x0000005a      0x7fffdffc      0x7ffffffc
0x0000000080206130 <bogus+     304>:    0x00000000      0x00000206      0x00005000      0x00000028
0x0000000080206140 <bogus+     320>:    0x00000001      0x00000001      0x00000040      0x000000fe
0x0000000080206150 <bogus+     336>:    0x00000000      0x00000000      0x80206400      0x80206200
0x0000000080206160 <bogus+     352>:    0x000000aa      0x00000080      0x00000034      0x00000002
0x0000000080206170 <bogus+     368>:    0x00000060      0x05050505      0x00000000      0x00000000
0x0000000080206180 <bogus+     384>:    0x00000000      0x00000000      0x00000006      0x00000000
0x0000000080206190 <bogus+     400>:    0x00000108      0x00000000      0x00000000      0x7ffffffc
0x00000000802061a0 <bogus+     416>:    0x00000010      0x00000000      0x00000000      0x00000000
0x00000000802061b0 <bogus+     432>:    0x00000000      0x00206000      0x8000490c      0x00000002
0x00000000802061c0 <bogus+     448>:    0x7fffff54      0x00000070      0x80207400      0x00000000
0x00000000802061d0 <bogus+     464>:    0x7fffff54      0x7fffff6c      0x00000000      0x00000000
0x00000000802061e0 <bogus+     480>:    0x00000010      0x00000008      0x00000010      0x00000010
0x00000000802061f0 <bogus+     496>:    0x00000000      0x00000000      0x00000000      0x00670000
