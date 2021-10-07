#include "netlist_simulator_controller/simulation_input.h"
#include "hal_core/netlist/gate.h"
#include "hal_core/netlist/net.h"

namespace hal {

    bool SimulationInput::contains_gate(const Gate* g) const
    {
        return (mSimulationSet.find(g) != mSimulationSet.end());
    }

    void SimulationInput::add_gates(const std::vector<Gate*>& gates)
    {
        mSimulationSet.insert(gates.begin(), gates.end());

        compute_input_nets();
        compute_output_nets();
    }

    const std::unordered_set<const Gate*>& SimulationInput::get_gates() const
    {
        return mSimulationSet;
    }

    bool SimulationInput::is_clock(const Net* n) const
    {
        for (const Clock& c: m_clocks)
            if (c.clock_net == n) return true;
        return false;
    }

    void SimulationInput::add_clock(const Clock& clk)
    {
        m_clocks.push_back(clk);
    }

    void SimulationInput::clear()
    {
        mSimulationSet.clear();
        m_clocks.clear();
        m_input_nets.clear();
        m_output_nets.clear();
    }

    bool SimulationInput::is_ready() const
    {
        return !mSimulationSet.empty() && !m_clocks.empty() && !m_input_nets.empty();
    }

    const std::vector<const Net*>& SimulationInput::get_input_nets() const
    {
        return m_input_nets;
    }

    const std::vector<const Net*>& SimulationInput::get_output_nets() const
    {
        return m_output_nets;
    }

    void SimulationInput::compute_input_nets()
    {
        m_input_nets.clear();
        for (auto gate : mSimulationSet)
        {
            for (auto net : gate->get_fan_in_nets())
            {
                // "input net" is either a global input...
                if (net->is_global_input_net())
                {
                    m_input_nets.push_back(net);
                }
                else    // ... or has a source outside of the simulation set
                {
                    for (auto src : net->get_sources())
                    {
                        if (!contains_gate(src->get_gate()))
                        {
                            m_input_nets.push_back(net);
                            break;
                        }
                    }
                }
            }
        }
    }

    void SimulationInput::compute_output_nets()
    {
        m_output_nets.clear();
        for (auto gate : mSimulationSet)
        {
            for (auto net : gate->get_fan_out_nets())
            {
                // "output net" is either a global output...
                if (net->is_global_output_net())
                {
                    m_output_nets.push_back(net);
                }
                else    // ... or has a destination outside of the simulation set
                {
                    for (auto dst : net->get_destinations())
                    {
                        if (!contains_gate(dst->get_gate()))
                        {
                            m_output_nets.push_back(net);
                            break;
                        }
                    }
                }
            }
        }
    }

}
