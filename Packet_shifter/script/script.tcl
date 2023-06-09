#!/usr/bin/tclsh 

set displayname {"PACKET SHIFTER " }
set functions "data_packet "
set clocks "10 "
cd ../ip
set index 0
foreach funcname $functions {
    open_project -reset $funcname
    puts "\n Generating function - $funcname \n"
    set filename "../src/"
    append filename $funcname ".cpp"
    add_files $filename

    open_solution $funcname
    set_top $funcname
    set_part [lindex $argv 2]
    create_clock -period [lindex $clocks $index] -name default
    config_bind -effort high
    config_schedule -effort medium  -relax_ii_for_timing=0 
    config_compile -name_max_length 100 -no_signed_zeros=0 -pipeline_loops 0 -unsafe_math_optimizations=0
    csynth_design
    #export_design -rtl verilog -format ip_catalog -description "An IP generated by 5G Testbed for NR" -vendor "5g_testbed" -library "NR" -display_name [lindex $displayname $index] -taxonomy "/WN"
    export_design -rtl verilog -format ip_catalog
    close_project
    incr index
}
puts "###################################################################"
puts " All the IPs are generated and available inside ip directory"
puts "###################################################################"
exit 