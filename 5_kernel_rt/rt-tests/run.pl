#!/usr/bin/perl

my @progs = ("./signaltest -l 10000","./pip_stress | ./pi_stress --duration 10","cyclictest --smp -h 40");

my $user = `whoami`;
chomp($user);

if($user != "root") {
	print STDERR "This script must be executed as root!\n";
	exit 1
}

my $kernel_version = `uname -r`;
my $using_rt = undef;
if (index($kernel_version, "SinRT") == -1) {
	$using_rt = 1;
}

my $out_file = undef;
if ($using_rt) {
	$out_file = "./rt.out";
} else {
	$out_file = "./wo_rt.out";
}
`rm -f $out_file`;

foreach $prog (@progs) {
	print STDOUT "Running $prog...";
	$out = `$prog`;
	`echo $out >> $out_file`;
	print STDOUT "DONE\n";
}
