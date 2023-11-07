#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    //  init top verilog instance
    Vcounter* top = new Vcounter;
    //  init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    //initialize simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    int holdCounter = 0;

    //run simulation for many clock cycles
    for (i=0; i<300; i++) {

        // dump variables in VCD files and toggle check
        for (clk = 0; clk<2; clk++){
            tfp->dump (2*i+clk);        //unit is in ps!!!
            top->clk = !top->clk;
            top->eval ();
        }
        top->rst = (i <2);
        if(top->count == 9){
            if(holdCounter < 3){
                holdCounter++;
                top->en = 0;
            } else {
                holdCounter = 0;
                top->en = 1;
            }
        } else {
        top->en = (i>4);
        }
    
        
        if(Verilated::gotFinish())  exit(0);
    }
    tfp->close();
    exit(0);
}
