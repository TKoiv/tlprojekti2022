#!/bin/bash

PATH="/usr/sbin:/sbin:/usr/bin:/bin"

#
# IPv4
#

# Clear old rules and set defaults
iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -F INPUT
iptables -F OUTPUT
iptables -F FORWARD
iptables -F -t nat
iptables -F -t mangle

# Local and trusted hosts and networks
iptables -A INPUT -i lo -j ACCEPT
iptables -A INPUT -s 192.168.0.0/24 -j ACCEPT # example how to allow whole IP network 192.168.0.xxx
iptables -A INPUT -s 193.167.100.97 -j ACCEPT # DO NOT COMMENT OR MODIFY THIS. THIS IS BACKDOOR TO YOUR SERVER FROM students.oamk.fi

# Completely open services
iptables -A INPUT -p tcp --dport 22 -j ACCEPT # DO NOT COMMENT OR MODIFY THIS. YOU WILL KICK YOURSELF OUT FROM THE SERVER (SSH)
iptables -A INPUT -p tcp --dport 80 -j ACCEPT # HTTP

# established traffic inbound (allow return traffic back which was originated from your server)
iptables -A INPUT -p ALL -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT

# Other SYN etc inbound

# Logging may generate too much log entries. This is commented now but left here as an example how to log:
# iptables -A INPUT -p ALL -m conntrack --ctstate NEW,INVALID -j LOG --log-prefix "DROP NEW "

# Drop all other new inbound but count dropped connections
iptables -A INPUT -p ALL -m conntrack --ctstate NEW,INVALID -j DROP 

# Dropping all example:
iptables -A INPUT -p ALL -j DROP

# Defaults
iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD DROP

#
# IPv6 (same logic as with IPv4)
#

ip6tables -P INPUT DROP
ip6tables -P OUTPUT ACCEPT
ip6tables -P FORWARD DROP
ip6tables -F INPUT
ip6tables -F OUTPUT
ip6tables -F FORWARD

ip6tables -A INPUT -i lo -j ACCEPT
ip6tables -A INPUT -p TCP --dport 22
ip6tables -A INPUT -m state --state  ESTABLISHED,RELATED -j ACCEPT
ip6tables -A INPUT -p icmpv6 -j ACCEPT # ICMP6  autoconfig etc router advertisements
ip6tables -A INPUT -j DROP

ip6tables -P INPUT ACCEPT
ip6tables -P OUTPUT ACCEPT
ip6tables -P FORWARD DROP


