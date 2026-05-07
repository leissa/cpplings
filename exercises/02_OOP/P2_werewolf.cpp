// project: werewolf
//
// Build a simplified Werewolf (Mafia) game using OOP concepts.
// In Werewolf, players have roles: Villagers try to survive,
// Werewolves try to eliminate Villagers at night.
// During the day, the village votes out a random player.
//
// Work through each part in order, later parts reuse earlier ones.
// Do not modify the TEST_CASEs.
//
// You are encouraged to use:
//   - std::string  instead of const char* for storing names and roles
//   - std::vector  instead of raw arrays for storing collections of players
// Both are included below. Using them will reduce manual memory management.
// The Standard Library will be convered in more details in later chapers.

#include <cstdlib>
#include <doctest/doctest.h>
#include <string>
#include <vector>

// ============================================================================
// PART 1: Define the base class
// ============================================================================

// TODO: Define a class 'Player' with:
//   - PRIVATE members:
//       std::string 'name'
//       bool 'alive'    (default true)
//       bool 'immune'   (default false, set by the Healer each night)
//   - a constructor taking a std::string name
//   - PUBLIC const member functions:
//       get_name()  -> returns const std::string&
//       is_alive()  -> returns alive
//       is_immune() -> returns immune
//   - a PUBLIC function 'set_immune(bool value)' that sets immune
//   - a PUBLIC function 'eliminate()':
//       if immune: set immune to false, do nothing else
//                 (immunity only blocks the werewolf night attack)
//       if not immune: set alive to false
//   - a PUBLIC function 'eliminate_force()':
//       always sets alive to false regardless of immunity
//       (used for the daytime village vote)
//   - a PUBLIC virtual function 'role()' returning std::string,
//     base returns "player"
//   - a PUBLIC virtual destructor
//   - a PUBLIC operator==(const char* other_name) const
//     returns true if name == other_name
//     (std::string supports == with const char* directly)

// TODO: define Player here

TEST_CASE("Part 1: base class") {
  Player p("Alice");
  CHECK(p.get_name() == "Alice");
  CHECK(p.is_alive() == true);
  CHECK(p.is_immune() == false);
  CHECK(p.role() == "player");

  // immunity blocks eliminate() but not eliminate_force()
  p.set_immune(true);
  p.eliminate();
  CHECK(p.is_alive() == true);   // survived the night attack
  CHECK(p.is_immune() == false); // immunity consumed

  p.set_immune(true);
  p.eliminate_force();
  CHECK(p.is_alive() == false); // daytime vote ignores immunity

  CHECK(p == "Alice");
  CHECK(!(p == "Bob"));
}

// ============================================================================
// PART 2: Derived classes
// ============================================================================

// TODO: Define four classes inheriting from Player.
// All constructors take a std::string name and pass it to Player.
// All override role() returning std::string, with the override keyword.
//
// class 'Villager'  -> role() returns "villager"
// class 'Werewolf'  -> role() returns "werewolf"
// class 'Seer'      -> role() returns "seer"
// class 'Healer'    -> role() returns "healer"
//   also has: void protect(Player* target)
//     calls target->set_immune(true) ONLY IF target is not 'this' Healer

// TODO: define Villager, Werewolf, Seer, Healer here

TEST_CASE("Part 2: roles") {
  Villager v("Alice");
  Werewolf w("Jacob");
  Seer s("Paul");
  Healer h("Claire");

  CHECK(v.role() == "villager");
  CHECK(w.role() == "werewolf");
  CHECK(s.role() == "seer");
  CHECK(h.role() == "healer");

  h.protect(&v);
  CHECK(v.is_immune() == true);

  h.protect(&h); // healer cannot protect themselves
  CHECK(h.is_immune() == false);
}

// ============================================================================
// PART 3: The Game class
// ============================================================================

// TODO: Define a class 'Game' with:
//   - PRIVATE members:
//       std::vector<Player*> 'players'
//       std::string 'winner'   initialized to "" (empty string means no winner
//       yet)
//
//   - a default constructor
//   - a deleted copy constructor
//   - hint: no destructor needed: std::vector and std::string manage their own
//   memory

//
//   - PUBLIC functions:
//       add(Player* p)       appends to players
//       get(int i) const     returns player at index i
//       size() const         returns number of players
//       has_winner() const   returns !winner.empty()
//       get_winner() const    returns winner
//
//   - PUBLIC counting functions:
//       count_alive() const
//         returns number of players where is_alive() == true
//       count_role(const std::string& role) const
//         returns number of alive players whose role() matches 'role'
//
//   - PRIVATE function 'check_winner()':
//       Only update winner if it is still empty (game not yet decided).
//       villagers win if all werewolves are eliminated
//       werewolves win if there are more werewolves left than there are
//       villagers otherwise leave winner unchanged
//
//   - PUBLIC function 'night_attack(Player* target)':
//       Eliminates a random non-werewolves, unless they are protected by
//       healer. Then calls check_winner()
//
//   - PUBLIC function 'day_vote(Player* target)':
//       Eliminates a random player, bypassing healer immunity.
//       Then calls check_winner()
//    hint: for a simple application like this, you can use 'vec[std::rand() %
//    vec.size()]' to get a random elemant from a vector 'vec'.
//

// TODO: define Game here

TEST_CASE("Part 3: game basics") {
  Villager v1("Alice");
  Villager v2("Bob");
  Werewolf w("Jacob");
  Seer s("Paul");

  Game game;
  game.add(&v1);
  game.add(&v2);
  game.add(&w);
  game.add(&s);

  CHECK(game.has_winner() == false);
  CHECK(game.size() == static_cast<std::size_t>(4));
  CHECK(game.count_alive() == 4);
  CHECK(game.count_role("werewolf") == 1);
  CHECK(game.count_role("villager") == 2);

  game.night_attack(&s);
  CHECK(s.is_alive() == false);
  CHECK(game.has_winner() == false);
  game.day_vote(&w);
  CHECK(w.is_alive() == false);
  CHECK(game.get_winner() == "villagers");
}

TEST_CASE("Part 3: werewolves eat village") {
  Villager v("Alice");
  Werewolf w1("Jacob");
  Werewolf w2("Angua");

  Game game;
  game.add(&v);
  game.add(&w1);
  game.add(&w2);

  game.night_attack(&v);
  CHECK(game.has_winner() == true);
  CHECK(game.get_winner() == "werewolves");
}

TEST_CASE("Part 3: immunity blocks night attack but not day vote") {
  Villager v("Alice");
  Werewolf w("Angua");
  Healer h("Claire");

  Game game;
  game.add(&v);
  game.add(&w);
  game.add(&h);

  h.protect(&v);
  game.night_attack(&v);
  CHECK(v.is_alive() == true);
  CHECK(game.count_alive() == 3);

  h.protect(&v);
  game.day_vote(&v);
  CHECK(v.is_alive() == false);
  CHECK(game.count_alive() == 2);
}

// ============================================================================
// PART 4: can_start and start
// ============================================================================

// TODO: Add to Game:
//
// bool can_start() const
//   Returns true if ALL of the following hold:
//     - at least 1 werewolve
//     - at least 1 villager
//     - at least 1 seer
//     - at least 1 healer
//     - non-wolves must be at least twice the number of wolves
//
// void start()
//   If can_start() is false, do nothing.
//   Otherwise simulate the game night by night.
//   Continue calling night_phase() then day_phase() until has_winner().
//
//   void night_phase():
//     (a) If a Healer is alive: find the first alive Healer in players,
//         collect all alive players that are NOT the Healer into
//         a std::vector<Player*>, then pick one at random and call
//         healer->protect(target).
//     (b) Collect all alive non-werewolves into a std::vector<Player*>.
//         Pick one at random and call night_attack(target).
//         Return if has_winner().
//
//   void day_phase():
//     (a) Collect all alive players into a std::vector<Player*>.
//         Pick one at random and call day_vote(target).
//         Return if has_winner().
//     (b) If no winner found, reset all healer immunities and go another
//     night.
//
// Using std::vector for candidate lists avoids any spinning loops:
// build the candidate list first, then index into it directly.

// TODO: add can_start(), start(), night_phase(), day_phase() to Game

TEST_CASE("Part 4: can_start") {
  Game empty;
  CHECK(empty.can_start() == false);

  // missing seer and healer
  Villager v("Alice");
  Werewolf w("Jacob");
  Game missing_roles;
  missing_roles.add(&v);
  missing_roles.add(&w);
  CHECK(missing_roles.can_start() == false);

  // all roles present, 3 non-wolves >= 2 * 1 wolf -> ok
  Villager v2("Bob");
  Seer s("Paul");
  Healer h("Claire");
  Game valid;
  valid.add(&v);
  valid.add(&v2);
  valid.add(&w);
  valid.add(&s);
  valid.add(&h);
  CHECK(valid.can_start() == true);

  // all roles present, 5 non-wolves >= 2 * 2 wolves -> ok
  Werewolf w2("Angua");
  Villager v3("Charlie");
  Seer s2("Bran");
  Healer h2("Greg");
  Game balanced;
  balanced.add(&v);
  balanced.add(&v2);
  balanced.add(&v3);
  balanced.add(&w);
  balanced.add(&w2);
  balanced.add(&s2);
  balanced.add(&h2);
  CHECK(balanced.can_start() == true);

  // all roles present, but 4 non-wolves < 2 * 3 wolves -> fails ratio
  Werewolf w3("Oz");
  Villager v4("Henry");
  Seer s3("Merlin");
  Healer h3("Luna");
  Game unbalanced;
  unbalanced.add(&v);
  unbalanced.add(&v4);
  unbalanced.add(&w);
  unbalanced.add(&w2);
  unbalanced.add(&w3);
  unbalanced.add(&s3);
  unbalanced.add(&h3);
  CHECK(unbalanced.can_start() == false);
}

TEST_CASE("Part 4: start produces a winner") {
  std::srand(42);

  Villager v1("Alice");
  Villager v2("Bob");
  Villager v3("Charlie");
  Werewolf w("Jacob");
  Seer s("Paul");
  Healer h("Claire");

  Game game;
  game.add(&v1);
  game.add(&v2);
  game.add(&v3);
  game.add(&w);
  game.add(&s);
  game.add(&h);

  game.start();

  CHECK(game.has_winner() == true);
  bool valid =
      game.get_winner() == "villagers" || game.get_winner() == "werewolves";
  CHECK(valid);
}

// ============================================================================
// PART 5: Find a player by name
// ============================================================================

// TODO: Implement find_player(game, name) returning a pointer to the
// first Player in the game where (player == name) is true, or nullptr.
// This uses operator==(const char*) defined in Part 1.

TEST_CASE("Part 5: find player") {
  Villager v("Alice");
  Werewolf w("Jacob");
  Seer s("Paul");
  Healer h("Claire");

  Game game;
  game.add(&v);
  game.add(&w);
  game.add(&s);
  game.add(&h);

  Player *found = find_player(game, "Jacob");
  CHECK(found != nullptr);
  CHECK(found->role() == "werewolf");

  Player *missing = find_player(game, "Zara");
  CHECK(missing == nullptr);

  // eliminated players are still findable
  game.day_vote(&w);
  Player *dead = find_player(game, "Jacob");
  CHECK(dead != nullptr);
  CHECK(dead->is_alive() == false);
}
