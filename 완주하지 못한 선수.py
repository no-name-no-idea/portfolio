def solution(participant,completion):

    temp = 0
    dic = {}
    
    
    participant.sort()
    completion.sort()

    for par in participant:
        dic[hash(par)] = par
        temp += int(hash(par))
    
    for com in completion:
        temp -= hash(com)
            
    return dic[temp]