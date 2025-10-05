#include "score.h"
#include "matchEngine.h"
#include "commentary.h"


#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;




// ANSI Color Codes
#define RESET   "\033[0m"
#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define WHITE   "\033[1;37m"



vector<string> sixCommentary = {
    
    "🚀 What a hit! That's out of the park!",
    
    "💣 BOOM! Straight into the stands!",
    
    "💥 That's a monster six — the crowd goes wild!",
    
    "🎯 Clean as a whistle! That's six more!",
    
    "🔥 He's absolutely smoked that one over long-on!",
    
    "🌪️ That's gone miles — what a strike!",
    
    "🎆 That ball's still travelling! Unbelievable power!",
    
    "⚡ That's a helicopter shot for a huge six!",
    
    "💪 Pure timing! Over the ropes effortlessly!",
    
    "🎯 The bowler can only watch — that's massive!",
    
    "💥 Out of the ground! That's a statement hit!",
    
    "😱 That's a 100-metre monster! What a strike!",
    
    "🏏 That's a six you'll remember for a long time!",
    
    "🎉 Into the second tier! The fans are on their feet!",
    
    "🔥 That's a brutal hit — bowler under pressure now!",

    "😱 History Will Remember For His Big Hitting!",

};



vector<string> fourCommentary = {
    
    "🎯 Beautifully timed! That races away for four!",
    
    "💥 Cracking shot through the covers — four runs!",
    
    "🔥 Pierced the gap perfectly — that's a boundary!",
    
    "🏏 Sweet timing! No need to run for that one!",
    
    "💨 Lightning fast! The ball speeds to the fence!",
    
    "🎆 Elegant stroke — pure class from the batter!",
    
    "⚡ That's a bullet to the boundary!",
    
    "💫 What placement! He found the gap with precision!",
    
    "🌈 Rolled his wrists beautifully — four more!",
    
    "🎯 That's textbook batting — exquisite timing!",
    
    "🚀 Crunched it! The fielders had no chance!",
    
    "🏖️ Threaded through the infield — that's four!",
    
    "💥 Another boundary! The bowler looks frustrated!",
    
    "🎨 That's a masterpiece of timing and control!",
    
    "💪 Firmly struck! One bounce and over the rope!"

};



vector<string> runCommentary = {
    
    "🏃 Quick single taken — great awareness between the wickets!",
    
    "👏 Smart running! They're keeping the scoreboard ticking.",
    
    "⚡ Sharp call and good response — easy one run.",
    
    "💨 They scamper through for a couple!",
    
    "🔥 Excellent running! Turned one into two there.",
    
    "🎯 Placed it perfectly into the gap for a single.",
    
    "🏏 Nudged into the off side — comfortable single.",
    
    "🌀 Quick couple! Good hustle between the wickets.",
    
    "💪 Pushed hard and they come back for two!",
    
    "⚡ Brilliant running — that's a quick three!",
    
    "🌪️ They've stolen a single right under the fielder's nose!",
    
    "🎯 Great communication — no confusion there!",
    
    "👏 Sensible batting — rotating the strike nicely.",
    
    "🏃 Fast between the wickets! That's good cricket.",
    
    "💨 Hustled hard for those runs — excellent teamwork!"

};




vector<string> wicketCommentary = {
    
    "💥 Clean Bowled! The stumps are shattered — what a delivery!",
    
    "😱 Edged and taken! Brilliant catch behind the stumps!",
    
    "🔥 Bowled him! That's a beauty — absolute peach of a delivery!",
    
    "🎯 LBW! That looked plumb — no doubt about it!",
    
    "💫 Gone! What a catch! He plucked it out of thin air!",
    
    "😬 Poor shot selection, and he pays the price!",
    
    "🎭 Oh no! A horrible mix-up — and he's run out!",
    
    "⚡ Direct hit! That's brilliant fielding!",
    
    "💥 Timberrrrr! The stumps light up!",
    
    "🧊 Soft dismissal — just chipped it straight to the fielder.",
    
    "🔥 The bowler is on fire! Another wicket bites the dust!",
    
    "💔 Big wicket! That's a huge breakthrough for the bowling side!",
    
    "😳 What was he thinking? Straight to the man!",
    
    "📉 Pressure builds and the batter cracks — wicket down!",
    
    "🎯 Clean strike on the pads — finger goes up instantly!",
    
    "😵 Edged to slip — safe hands, he's gone!",
    
    "🤯 Unbelievable! What a diving catch — that's world-class!",
    
    "😔 Tried to go big, but finds the fielder in the deep!",
    
    "💣 Knocked him over! The crowd erupts!",
    
    "🙌 Another one bites the dust! Great teamwork in the field!"

};



vector<string> dotBallCommentary = {
    
    "⏳ No run! Dot ball — pressure building on the batter.",
    
    "🛑 Tight bowling — batter couldn't get any runs off that.",
    
    "🎯 Excellent delivery, well defended — dot ball!",
    
    "💨 Pitched up and defended — scoreboard stays still.",
    
    "⚡ Good length ball, no room to score!",
    
    "🧊 Calm and composed shot — still no run.",
    
    "🔒 Dot ball! The bowler is building pressure beautifully.",
    
    "🏏 Nice leave — nothing to do for the batter.",
    
    "🔥 Batter tried to attack, but well stopped — dot ball!",
    
    "🎭 Clever fielding, clever bowling — dot ball!",
    
    "💫 Good defensive stroke — no run taken.",
    
    "⚡ A careful shot — but the field holds strong!",
    
    "🌀 Dot ball! The bowler is forcing mistakes.",
    
    "💪 Solid defense — the batter survives this one.",
    
    "⏱️ Another dot! The pressure mounts on the batting side."

};



vector<string> userWinComments = {
    
    "What a sensational victory! The crowd is going wild!",
    
    "Incredible performance! They've defended the total like true champions!",
    
    "Nerves of steel! A brilliant win for the home side!",
    
    "What a finish! They held their composure and came out on top!",
    
    "A complete team effort! Every player contributed to this memorable win!",
    
    "They've done it! A stunning display of skill and strategy!",
    
    "Victory snatched from the jaws of defeat — what a game!",
    
    "The players are celebrating — and rightly so! That's a well-deserved win!"

};


vector<string> userLoseComments = {
    
    "Oh no! That's heartbreaking — they were so close!",
    
    "A crushing defeat, but they fought hard till the end!",
    
    "The opposition chased it down in style — what a batting show!",
    
    "Tough luck today! The bowlers gave it their all, but it wasn't enough.",
    
    "Disappointment for the fans, but plenty of positives to take from this match.",
    
    "Outclassed today, but every defeat is a lesson for the next battle!",
    
    "The AI team finishes it off — dominant performance from them!",
    
    "A tough pill to swallow, but what an entertaining match it was!"

};



vector<string> tieComments = {
    
    "Unbelievable! It's a tie! You don't see this every day!",
    
    "What a thriller — neither team could be separated!",
    
    "Both sides gave their all! A fitting end to an epic contest!",
    
    "Incredible match — it ends in a tie! Cricket truly is the winner!",
    
    "What a game! It went right down to the wire and no one blinked!",
    
    "A nail-biting finish ends in a draw — both teams can hold their heads high!",
    
    "Wow! After all that drama, it's still even! What a spectacle!",
    
    "A match for the ages — both teams share the honors!"

};












void scoreCard(int score, int wicket, int ballCount, int target, string teamName, int totalBalls) {

    int overs = ballCount / 6;
    
    int balls = ballCount % 6;
    
    int totalOvers = totalBalls / 6;

    float runRate = (ballCount > 0) ? ((float)score / (float)(ballCount / 6.0)) : 0.0;
    
    float requiredRunRate = 0.0;

    if (target > 0 && score < target) {
        
        int remainingBalls = totalBalls - ballCount + 1;
        
        int runsNeeded = target - score;
        
        requiredRunRate = (remainingBalls > 0) ? ((float)runsNeeded / (float)(remainingBalls / 6.0)) : 0.0;
    
    }

    cout << CYAN;
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║ " << YELLOW << setw(79) << left << ("🏏 TEAM: " + teamName) << CYAN << "║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";

    cout << "║ " << WHITE << "Score: " << GREEN << setw(70) << left << (to_string(score) + "/" + to_string(wicket)) << CYAN << "║\n";
    cout << "║ " << WHITE << "Overs: " << BLUE << setw(70) << left << (to_string(overs) + "." + to_string(balls) + "/" + to_string(totalOvers)) << CYAN << "║\n";
    cout << "║ " << WHITE << "Run Rate: " << GREEN << setw(67) << left << fixed << setprecision(2) << runRate << CYAN << "║\n";

    if (target > 0) {
        
        int remainingBalls = totalBalls - ballCount + 1;
        
        int runsNeeded = target - score;
        
        if (runsNeeded > 0) {
            cout << "║ " << WHITE << "Target: " << YELLOW << setw(69) << left << to_string(target) << CYAN << "║\n";
            cout << "║ " << WHITE << teamName << " Need " << RED << runsNeeded << WHITE << " Runs From " << RED << remainingBalls << WHITE << " Balls" << setw(47) << CYAN << "║\n";
            cout << "║ " << WHITE << "Required Run Rate: " << YELLOW << setw(58.2) << left << fixed << setprecision(2) << requiredRunRate << CYAN << "║\n";
        }
        
        else {
            
            cout << "║ " << GREEN << setw(74) << left << "🏆 Target Achieved! Innings Over!" << CYAN << "║\n";
        
        }
    
    }
    
    else {
        
        cout << "║ " << WHITE << "Target: " << YELLOW << setw(69) << left << "To Be Decided (First Innings)" << CYAN << "║\n";
    
    }

    cout << "╠══════════════════════════════════════════════════════════════════════════════╣\n";

    // Progress Bar for Overs
    
    cout << "║ Overs Progress: [";
    
    int progressBarWidth = 30;
    
    int progress = round(((float)ballCount / totalBalls) * progressBarWidth);
    
    for (int i = 0; i < progressBarWidth; i++) {
        
        cout << (i < progress ? GREEN "█" CYAN : " ");
    
    }
    
    cout << "]" << setw(59 - progressBarWidth) << " " << "║\n";

    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";
    cout << RESET;

    // Commentary / Situational Messages
    
    if (target > 0 && score < target) {
        
        int remainingBalls = totalBalls - ballCount + 1;
        
        int runsNeeded = target - score;

        if (remainingBalls <= 12)
            cout << RED << "⚡ Pressure Building! " << runsNeeded << " needed off " << remainingBalls << " balls!\n" << RESET;
        else if (runsNeeded < 15)
            cout << GREEN << "🔥 Almost there! Just a few runs away from victory!\n" << RESET;
    }
    
    else if (wicket == 10) {
        
        cout << RED << "💥 All Out! Innings Over.\n" << RESET;
    
    }

    cout << "\n";

}















void scoreLogic(int &stamina, int batChoice, int who, int temperature, string ballType, string pitchType) {

    // -------------------- Pitch & Ball Modifiers --------------------
    
    float scoreMultiplier = 1.0;
    
    float wicketMultiplier = 1.0;

    
    if (pitchType == "Green") {
        
        if (ballType == "In_Swing" || ballType == "Out_Swing" || ballType == "Pace" || ballType == "Bouncer") {
            
            scoreMultiplier = 0.9f;
            
            wicketMultiplier = 1.1f;
        
        }
    
    }
    
    else if (pitchType == "Dusty") {
        
        if (ballType == "Leg_Spin" || ballType == "Off_Spin" || ballType == "Slower" || ballType == "Arm_Ball") {
            
            scoreMultiplier = 0.85f;
            
            wicketMultiplier = 1.2f;
        
        }
    
    }
    
    else if (pitchType == "Soft") {
        
        scoreMultiplier = 1.1f;
        
        wicketMultiplier = 0.9f;
    
    }




    // -------------------- Base Wicket Probability --------------------
    
    int baseWicketChance;
    
    if (stamina >= 90) baseWicketChance = 5;
    
    else if (stamina >= 70) baseWicketChance = 15;
    
    else if (stamina >= 50) baseWicketChance = 25;
    
    else if (stamina >= 30) baseWicketChance = 35;
    
    else if (stamina >= 20) baseWicketChance = 45;
    
    else baseWicketChance = 55;

    
    int wicketChance = (int)(baseWicketChance * wicketMultiplier);
    
    if (wicketChance > 95) wicketChance = 95;

    
    
    
    
    
    
    
    
    
    // -------------------- Shot Risk Adjustment --------------------
    
    string shot = batVariation[batChoice];
    
    if (shot == "LoftShot")      wicketChance += 8;
    
    else if (shot == "StrikeShot") wicketChance += 3;
    
    else if (shot == "Defend")     wicketChance -= 15;

    if (wicketChance < 0) wicketChance = 0;

    
    
    
    
    
    // Extra risk for very low stamina
    
    if (stamina < 10) wicketChance += 20;
    
    if (wicketChance > 95) wicketChance = 95;






    // -------------------- Determine Wicket --------------------
    
    bool out = false;
    int runs = 0;

    if (shot == "Defend") {
        
        out = (rand() % 100 < 1);
    
    }
    
    else {
    
        out = (rand() % 100 < wicketChance);
    
    }

    
    
    
    
    
    
    
    // -------------------- Runs Distribution --------------------
    
    if (!out) {
        
        int randomVal = rand() % 100;
        
        if (shot == "LoftShot") {
            
            int c6 = (stamina > 50) ? 15 : 5;
            
            int c4 = (stamina > 50) ? 25 : 15;
            
            int c3 = 20;
            
            int c2 = 20;
            
            runs = (randomVal < c6) ? 6 :
                   (randomVal < c6 + c4) ? 4 :
                   (randomVal < c6 + c4 + c3) ? 2 :
                   (randomVal < c6 + c4 + c3 + c2) ? 1 : 0;
        
        }
        
        else if (shot == "StrikeShot") {
            
            int c4 = 25;
            
            int c3 = 30;
            
            int c2 = 25;
            
            runs = (randomVal < c4) ? 4 :
                   (randomVal < c4 + c3) ? 2 :
                   (randomVal < c4 + c3 + c2) ? 1 : 0;
        
        }
        
        else if (shot == "StrikeRotate") {
            
            int c3 = 10, c2 = 25, c1 = 50;
            
            runs = (randomVal < c3) ? 3 :
                   (randomVal < c3 + c2) ? 2 :
                   (randomVal < c3 + c2 + c1) ? 1 : 0;
        
        }
        
        else if (shot == "Defend") {
            
            runs = (randomVal < 70) ? 0 :
                   (randomVal < 90) ? 1 : 2;
        
        }

        
        
        // Apply score multiplier
        
        if (shot == "Defend" || shot == "StrikeRotate")
            runs = int(round(runs * scoreMultiplier));
        else
            runs = max(1, int(round(runs * scoreMultiplier)));
        
        if (runs > 6) runs = 6;
        
        if (runs == 5) runs = 4;

        
        
        // Reduce big shots for very low stamina
        if (stamina < 20 && (runs == 6 || runs == 4)) runs = 2;

        if (stamina >= 95) {
            
            if (shot == "LoftShot") runs = 6;

            else if (shot == "StrikeShot") runs = 4;
            
            else if (shot == "StrikeRotate") runs = 3;
        
        }
        
        else if (stamina >= 90) {
            
            if (shot == "LoftShot" || shot == "StrikeShot") runs = 4;
            
            else if (shot == "StrikeRotate") runs = 3;
        
        }
    
    }

    
    
    
    // -------------------- Update Score --------------------
    
    if (out) {
        
        cout << "Commentary: " << wicketCommentary[rand() % wicketCommentary.size()] << "\n";
        
        cout << "Shot Played: " << shot << "\n";
        
        cout << "Shot Outcome: Wicket\n";
        
        if (who == 1) userWicket++;
        
        else aiWicket++;
    
    }
    
    else {
        
        if (who == 1) userScore += runs;
        
        else aiScore += runs;

        if (runs == 6) cout << "Commentary: " << sixCommentary[rand() % sixCommentary.size()] << "\n";
        
        else if (runs == 4) cout << "Commentary: " << fourCommentary[rand() % fourCommentary.size()] << "\n";
        
        else if (runs > 0) cout << "Commentary: " << runCommentary[rand() % runCommentary.size()] << "\n";
        
        else cout << "Commentary: " << dotBallCommentary[rand() % dotBallCommentary.size()] << "\n";

        cout << "Shot Played: " << shot << "\n";
        
        cout << "Shot Outcome: " << runs << "\n";
    
    }

    
    
    
    // -------------------- Stamina Adjustment --------------------
    
    if (shot == "Defend") {
        
        int gain = (stamina < 60) ? 8 : (stamina < 90 ? 6 : 3);
        
        stamina += (temperature >= 40) ? gain - 2 : gain;
        
        if (stamina > 100) stamina = 100;
    
    }
    
    else {
        
        int loss = (runs >= 6) ? 5 : (runs >= 4 ? 4 : (runs > 0 ? 2 : 1));
        
        if (temperature >= 40) loss += 1;
        
        stamina -= loss;
        
        if (stamina < 0) stamina = 0;
    
    }

}

