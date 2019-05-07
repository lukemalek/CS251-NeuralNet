#include "Neural_net.h"
#include "sd_fun.h"

string toString(char *yaml, Range r)
{
    string result;
    for (int i = 0; i < r.len; i++)
    {
        result.push_back(yaml[r.pos + i]);
    }
    return result;
}

int main()
{
    init();

    Network *AI;

    if (length_of(yaml) < 50)
    {
        Network myBot("english.net");
        AI = &myBot;
        mem[500] = 0;
        write_at(mem, 0, "The Magic Language-Determiner");
        write_at(mem, 50, "enter a phrase");
        write_at(mem, 150, "I think that is english.");
        write_at(mem, 180, "I think that is gibberish.");
    }
    

    int guess = 0;
    Range t_range = find_value(yaml, "content:");
    yaml[0] = 0;
    if (t_range.len > 0)
    {
        /*
        string sentence = toString(yaml, t_range);
        AI->setInputLayer(formToInput(sentence, AI->getInputSize(), true));
        AI->evaluate();
        
        if (AI->getOutput(0) > AI->getOutput(1))
        {
            guess = 1;
        }
        else
        {
            guess = 2;
        }
        */
        write_at(mem, 0, "you entered a wordddd");
    }
    write_at(mem, 50, (long)AI);
    append(yaml, R"(
    Text_top:
      style:
        color: black
        fontSize: 60
        marginLeft: 10
      pos: 0
      len: 35)");
    append(yaml, R"(
    Text_prompt:
      style:
        color: black
        fontSize: 30
        marginLeft: 10
      pos: 50
      len: 90)");
    append(yaml, R"(
    TextInput_1:
      style:
        position: absolute
        marginTop: 110
        width: 1000
        height: 35
        fontSize: 25
        borderColor: 'gray'
        borderWidth: 2
      pos: 500
      len: 100)");
    if (guess == 1)
    {
        append(yaml, R"(
        Text_guess:
            style:
                color: black
                fontSize: 30
                marginTop: 50
            pos: 150
            len:28)");
    }
    if (guess == 2)
    {
        append(yaml, R"(
        Text_guess:
            style:
                color: black
                fontSize: 30
                marginTop: 50
            pos: 180
            len:28)");
    }
    mem[500] = 0; // initialize the text area to be empty

    quit();
}