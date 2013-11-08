#!/usr/bin/perl

my $who = `whoami`;
chomp($who);

if($who ne "root") {
	print "This script must be executed as root!\n";
	exit -1;
}

my $module = "myblkdrv";
my $driver = "$module.ko";

my $res = `lsmod | grep $module`;

if($res ne "") {
	print "Unloading module... ";
	`sudo rmmod $module`;
	print "Done\n";
} else {
	print "Module was not loaded, so it's not need to remove it\n";
}

print "Compiling the module\n";
`make`;

print "Loading the module... ";
`insmod ./$driver`;
print "Done\n";
