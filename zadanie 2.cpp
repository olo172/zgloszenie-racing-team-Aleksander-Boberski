#include<iostream>
#include<vector>
using namespace std;

bool comp(pair<double, double> a, pair<double, double> b, pair<double, double> c, bool b_in_hull, bool c_in_hull) //komparator uzywany do szukania nastepnego punktu
//a - poprzedni punkt, b,c - punkty obecnie porownywane, b_in_hull - zmienna mowiaca czy b jest juz w otoczce, c_in_hull - analogicznie dla c
{
    if(a.first == b.first and a.second == b.second) return true; //jesli a = b to dopiero zaczynamy wyszukiwanie wiec dowolny punkt pasuje

    pair<double, double> AB = {b.first-a.first, b.second-a.second}; //wektor ab
    pair<double, double> AC = {c.first-a.first, c.second-a.second}; //wektor ac

    if((AB.second*AC.first) - (AB.first*AC.second) < 0) return true; //c jest po lewej stronie wektora ab
    if((AB.second*AC.first) - (AB.first*AC.second) == 0) //a,b,c sa na jednej linii - przypadek brzegowy
        return ( (AB.first*AB.first)+(AB.second*AB.second) > (AC.first*AC.first)+(AC.second*AC.second) and !c_in_hull ) or (b_in_hull and !c_in_hull);
    return false; //c jest po prawej stronie wektora ab
}
int find_next_point(int last_point, vector<pair<double, double>> points, vector<bool> in_hull)
{
    int next_point = last_point; //poczatkowo ustawiamy poprzedni punkt jako nastepny
    for(int i = 0; i < points.size(); i++) //funkcja iteruje po wszystkich punktach w celu znalezienia punktu "najbardziej na lewo"
        if(comp(points[last_point], points[next_point], points[i], in_hull[next_point], in_hull[i])) next_point = i;
    return next_point;
}
vector<pair<double, double>> find_hull(vector<pair<double, double>> points)
{
    vector<pair<double, double>> hull; //lista punktow tworzacych otoczke
    vector<bool> in_hull; //jezeli in_hull[i] == true to punkt i nalezy juz do otoczki
    int p;
    for(int i = 0; i < points.size(); i++) //szukanie punktu o najmniejszym x(y)
    {
        if( (points[i].first < points[p].first) or (points[i].first == points[p].first and points[i].second < points[p].second) ) p = i;
        in_hull.push_back(false);
    }
    hull.push_back(points[p]); //dodajemy do otoczki punkt startowy
    in_hull[p] = true;

    p = find_next_point(p, points, in_hull);
    while(!in_hull[p]) //znajdujemy kolejne punkty otoczki dopoki nie powstanie zamkniety cykl
    {
        hull.push_back(points[p]);
        in_hull[p] = true;
        p = find_next_point(p, points, in_hull);
    }
    return hull; //zwracanie listy punktow w otoczce
}
void program()
{
    int n;
    double a, b;
    vector<pair<double, double>> points;
    cin >> n;
    while(n--) //wczytywanie danych
    {
        cin >> a >> b;
        points.push_back({a,b});
    }

    vector<pair<double, double>> hull = find_hull(points); //generowanie odpowiedzi
    cout << "[";
    for(pair<double, double> point : hull) cout << "(" << point.first << ", " << point.second << "), "; //wypisywanie odpowiedzi
    cout << "]\n";
    return;
}

int main()
{
    program();
    return 0;
}
