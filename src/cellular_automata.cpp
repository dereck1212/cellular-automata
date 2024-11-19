#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <cstdlib>
#include <fstream>

class cellular_automata 
{
protected:
    bool rules[8];
    std::vector<bool> state;
public:
    cellular_automata(const bool set_rule[8], const std::vector<bool>& initial_state) 
    {
        // Copy rules
        for(int i = 0; i < 8; i++) 
        {
            rules[i] = set_rule[i];
        }
        // Copy initial state
        state = initial_state;
    }
    //cellular_automata(){}

    virtual std::vector<bool>  next() 
    {
        std::vector<bool> new_state = state;  // Create a copy to store new states
        
        for (int i = 0; i < state.size(); i++) 
        {
            // Calculate indices with wrap-around
            int previous = (i == 0) ? state.size() - 1 : i - 1;
            int next = (i == state.size() - 1) ? 0 : i + 1;
            
            // Calculate rule index (4*left + 2*center + 1*right)
            int index_rule = (state[previous] << 2) | (state[i] << 1) | state[next];
            
            // Apply rule
            new_state[i] = rules[7 - index_rule];  // Note: 7-index_rule to match standard convention
        }
        
        state = new_state;  // Update the state
        return state;
    }
};

class random_cellular_automata : public cellular_automata
{
protected:
double p;

public:
    random_cellular_automata(const bool set_rule[8], const std::vector<bool>& initial_state, const double p_set) : cellular_automata(set_rule,initial_state)
    {

        for(int i=0; i<8; i++)
        {
            rules[i]= set_rule[i];
        }
        state = initial_state;
        p=p_set;
    }

    std::vector<bool> next() override
    {
    double random_0_to_1 =  (double)rand() / RAND_MAX;
    if(random_0_to_1<p)
    {
    std::vector<bool> new_state = state ;
    int random_index = rand() % state.size();
    new_state[random_index] = (bool)(rand() % 2);
    state=new_state;
    }
    else
    {
    state = cellular_automata::next();
    }
    return state;
    }


};


int main()
{

    std::string file_name, rules_string, initial_state_string;
    bool rules_converted[8];
    std::vector<bool> initial_state_converted, current_state_converted;
    int k;
    double p;

    //user inputs
    std::cout<<" enter the path of the file ";
    std::cin >> file_name;
    std::cout<<" combien de generations voulez vous voir ? ";
    std::cin>> k;
    std::cout<< "entrez une probabilité de mutation aléatoire ";
    std::cin>>p;

    // file reading 
    try
    {
        std::ifstream file(file_name);
        if(!file.good())
        {
            throw std::runtime_error("file does not exist or cannot be opened: " + file_name);
        }
        // File exist and is opened successfully
        std::cout << "File exists and opened successfully"<<std::endl;

        // file operations here 
        std::getline(file, initial_state_string);
        std::getline(file, rules_string);
        file.close();
        
    }
    catch (const std::runtime_error& e)
    {
    std::cerr <<"Runtime error "<<e.what() << std::endl;
    }
    // conversions 
    for(int i=0; i<8; i++)
    {
        rules_converted[i] = (rules_string[i] == '1');
    }
    for (int i=0; i<initial_state_string.size(); i++)
    {
        initial_state_converted.push_back(initial_state_string[i]=='1');
    }
    //creating the automaton based on the rule and initial state stored in the file
    random_cellular_automata automaton(rules_converted, initial_state_converted,p);
    // creating a new file with same name and changing the extention to .pbm
    
    int size_t, lastDot = file_name.find_last_of('.');
    if (lastDot != std::string::npos)
    {
    file_name = file_name.substr(0, lastDot);
    }
    //writing the output file
    std::ofstream out_file(file_name+".pbm");
    out_file<<"P1"<<std::endl;
    int input_size = initial_state_string.size();
    out_file<<input_size<<" "<<k<<std::endl;

    for (int i=0; i<input_size;i++)
    {
    out_file<<initial_state_converted[i];
    }
    out_file<<std::endl;

    
    for(int i=0;i<k-1; i++)
    {
        current_state_converted=automaton.next();
    
        for (int j=0; j<input_size;j++)
        {
        out_file<<current_state_converted[j];
        }
        out_file<<std::endl;


    }

    return 0;
}
