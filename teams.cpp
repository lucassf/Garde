#include <bits/stdc++.h>
using namespace std;
typedef pair<double,double> dd;

struct team{
    int points, goal_balance, pro_goals;
    int id;
    string name;

    team(){}
    team(string _name,int _points,int _goal_balance,int _pro_goals, int _id){
        name = _name;
        points = _points, goal_balance = _goal_balance, pro_goals = _pro_goals;
        id = _id;
    }

    team win(){
        return team(name,points+3,goal_balance+1,pro_goals+1,id);
    }
    team draw(){
        return team(name,points+1,goal_balance,pro_goals+1,id);
    }
    team lose(){
        return team(name,points,goal_balance-1,pro_goals,id);
    }

    bool operator<(team other)const{
        if (points!=other.points)
            return points>other.points;
        if (goal_balance!=other.goal_balance)
            return goal_balance>other.goal_balance;
        return pro_goals>other.pro_goals;
    }
};

struct game{
    int team1_id,team2_id;
    double pwin, pdraw, plose;

    game(){}
    game(int t1,int t2,double pw,double pd,double pl){
        team1_id = t1, team2_id = t2, pwin = pw, pdraw = pd, plose = pl;
    }
};

void recursion(int index,vector<team> &teams,vector<game> &games,vector<dd> &probs,double prob){
    if (index == games.size()){
        vector<team> aux_teams = teams;
        sort(aux_teams.begin(),aux_teams.end());
        for (int i=0;i<4;i++)
            probs[aux_teams[i].id].first += prob;
        probs[aux_teams[4].id].second += prob;
        return;
    }

    int team1_id = games[index].team1_id;
    int team2_id = games[index].team2_id;
    team team1,team2;
    team1 = teams[team1_id];
    team2 = teams[team2_id];

    teams[team1_id] = team1.win();
    teams[team2_id] = team2.lose();
    recursion(index+1,teams,games,probs,prob*games[index].pwin);

    teams[team1_id] = team1.draw();
    teams[team2_id] = team2.draw();
    recursion(index+1,teams,games,probs,prob*games[index].pdraw);

    teams[team1_id] = team1.lose();
    teams[team2_id] = team2.win();
    recursion(index+1,teams,games,probs,prob*games[index].plose);

    teams[team1_id] = team1;
    teams[team2_id] = team2;
}

vector<dd> getClassProb(vector<team> &teams,vector<game> &games){
    vector<dd> probs;
    probs.assign(teams.size(),dd(0,0));

    recursion(0,teams,games,probs,1);

    return probs;
}

int main(){
    vector<team> teams;
    vector<game> games;

    teams.push_back(team("Brasil",38,27,38,0));
    teams.push_back(team("Uruguai",28,10,28,1));
    teams.push_back(team("Argentina",25,1,16,2));
    teams.push_back(team("Colombia",26,2,20,3));
    teams.push_back(team("Peru",25,1,26,4));
    teams.push_back(team("Chile",26,2,26,5));
    teams.push_back(team("Paraguai",24,-5,19,6));
    teams.push_back(team("Equador",20,-1,25,7));
    teams.push_back(team("Bolivia",14,-20,14,8));
    teams.push_back(team("Venezuela",9,-17,18,9));

    games.push_back(game(0, 5, 0.7, 0.2, 0.1));
    games.push_back(game(7, 2, 0.3, 0.2, 0.5));
    games.push_back(game(4, 3, 0.3, 0.4, 0.3));
    games.push_back(game(1, 8, 0.65, 0.15, 0.2));
    games.push_back(game(6, 9, 0.5, 0.25, 0.25));

    vector<dd> probs = getClassProb(teams,games);

    printf("%15s|%20s|%20s\n\n","Selecao","Prob. Classificar","Prob. Repescagem");
    for (int i=0;i<probs.size();i++){
        printf("%15s|%20.2lf|%20.2lf\n",teams[i].name.c_str(),probs[i].first*100,probs[i].second*100);
    }
    char ok;
    printf("\nPressiona enter para sair...\n");
    scanf("%c",&ok);
}
