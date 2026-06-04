// ============================================================================
// BACKGROUND: The Curry-Howard Correspondence
// ============================================================================
//
// In formal logic, a proposition is a statement that is either true or false.
// A proof is a demonstration that a proposition is true.
//
// The Curry-Howard correspondence is a concept from Types and Programming
// Languages Theoery that demonstrates the connection between logic and
// programming: propositions correspond to types, and proofs correspond to
// values of those types.
//
//   proposition P is provable  <->  type P is inhabited (has a value)
//   a proof of P               <->  a value of type P
//   a proof of P => Q          <->  any callable (function) mapping P to Q
//
// This means we can encode logical reasoning directly in C++ types, all at
// compile time:
//   - If we can construct a value of type P, we have proved P
//   - If no value of type P can be created, P is unprovable
//   - A callable f : P -> Q is a proof that P implies Q
//
// ============================================================================
// WHAT THIS PROJECT BUILDS
// ============================================================================
//
// You will build a small compile-time proof assistant for propositional logic.
// The connectives are:
//
//   And<P,Q>         P and Q - proved by holding both proofs
//   Or<P,Q,IsLeft>   P or Q  - proved by holding ONE proof,
//                              which side is encoded in the TYPE
//   Proves<F,P,Q>    concept: F is a proof of P => Q
//   ProvesNot<F,P>   concept: F is a proof of Not P
//   Contradiction    the unprovable proposition (cannot be instantiated due to
//   deleted constructor)
//
// ============================================================================
// THE CORRECTNESS GUARANTEE
// ============================================================================
//
// All proofs are verified at compile time using static_assert.
// There is no runtime content in this project.
// If the file compiles, every proof is valid.
// The compiler is the proof checker!
//
// If you like this topic and want to learn about the theory, consider attending
// our Types and Programming Languages Course
//
// ============================================================================
// Work through each part in order. Do not modify the static_asserts.
// ============================================================================

#include <concepts>
#include <type_traits>

// The only built-in unprovable proposition.
// Its constructor is deleted, no value of this type can ever be created.
// This is what makes ProvesNot meaningful and the system sound.
struct Contradiction {
  Contradiction() = delete;
};

// ============================================================================
// PART 1: Propositions and axioms
// ============================================================================

// A proposition is ANY type. A proof of P is a value of type P.
// YOU define what is provable by providing constexpr axiom functions.
// Anything without an axiom is unprovable by convention.
// Contradiction is the only exception, since it is always unprovable.
//
// TODO: Define three proposition types (empty structs): 'Rain', 'Wet', 'Cold'
//
// TODO: Define constexpr axiom functions:
// - 'axiom_rain',
// - 'axiom_wet',
// - 'axiom_cold'
// that return an empty struct initializer '{}' for their corresponding types.
// These are our starting assumptions, everything else must be derived.

// Test_Case
// everything done at compile time, doctest not needed.

static_assert(std::is_same_v<decltype(axiom_rain()), Rain>);
static_assert(std::is_same_v<decltype(axiom_wet()), Wet>);
static_assert(std::is_same_v<decltype(axiom_cold()), Cold>);

// ============================================================================
// PART 2: The Proves concept and apply
// ============================================================================

// A proof of P => Q is any callable F such that f(p) produces a Q.
// The Proves concept captures this constraint.
// apply is modus ponens: given a callable proving P => Q and a proof
// of P, produce a proof of Q.
//
// TODO: Define a concept Proves such that:
//    - takes 3 template typenames F, P, Q
//    - it requires f of type F, and p of type P, where calling f with p returns
//    the (same) type Q

// TODO: Define a constexpr function 'apply' such that:
//    - takes 2 template typenames F and P as arguments
//    - has a trailing retrun type that is deduced by the compiler using
//    decltype
//    - retruns f called with p
//
// NOTE: apply deduces its return type from decltype(f(p)) rather than
// taking Q as an explicit template parameter. This is necessary because
// the compiler cannot deduce Q from F and P alone — it would need to
// instantiate F to know its return type.

// Test_Case
static_assert(Proves<decltype([](Rain) { return Wet{}; }), Rain, Wet>);
static_assert(!Proves<decltype([](Rain) { return Cold{}; }), Rain, Wet>);

constexpr Wet part2_result = apply([](Rain) { return Wet{}; }, axiom_rain());
static_assert(std::is_same_v<std::remove_const_t<decltype(part2_result)>, Wet>);

// ============================================================================
// PART 3: Conjunction - AND
// ============================================================================

// And<P,Q> holds when BOTH P and Q hold.
// Storing both proofs is safe: to call prove_and(p,q) you must already
// hold valid values of P and Q, so the proofs genuinely exist.
//
// TODO: Define a struct template And<P,Q> with:
//   - PUBLIC constexpr constructor taking P and Q
//   - PUBLIC members: P left; Q right;
//
// TODO: Define constexpr functions:
//   - 'prove_and(P p, Q q)'  : bundles both proofs in struct And<P,Q>
//   - 'and_left(And<P,Q> a)' : extracts left proof of type P
//   - 'and_right(And<P,Q> a)': extracts right proof of type Q

// TODO: define And, prove_and, and_left, and_right here

constexpr And<Rain, Wet> part3_conj = prove_and(axiom_rain(), axiom_wet());
static_assert(std::is_same_v<decltype(and_left(part3_conj)), Rain>);
static_assert(std::is_same_v<decltype(and_right(part3_conj)), Wet>);

// ============================================================================
// PART 4: Disjunction - OR
// ============================================================================

// Or<P,Q,IsLeft> holds if AT LEAST ONE of P or Q holds.
// It stores exactly ONE proof, the one that was actually provided.
// Which side is stored is encoded in the type via the bool parameter IsLeft
// and std::conditional_t such that we can create a type proof_t where:
//
// - IsLeft == true:  proof_t is P  (or_left was called)
// - IsLeft == false: proof_t is Q  (or_right was called)
//
// This means the inactive side is NEVER constructed. If one side is
// Contradiction, we must never attempt to construct it.
//
// TODO: Define a struct template Or<P,Q,IsLeft> with:
//   - a using declatration to define proof_t as a std::conditional_t of P and Q
//   over IsLeft
//   - PUBLIC constexpr explicit constructor taking proof_t
//   - PUBLIC member: proof_t proof
//
// TODO: Define constexpr functions:
//   - 'or_left(P p)' : returns a struct Or<P,Q,true>
//   - 'or_right(Q q)': returns a struct Or<P,Q,false>
//
// NOTE: This design means or_left and or_right return different types:
//     or_left<Q>(p)  returns Or<P,Q,true>
//     or_right<P>(q) returns Or<P,Q,false>
//   The "which-side" information is in the type, not stored as a
//   runtime bool. This enables compile-time dispatch via overloads without the
//   need for tagged unions or structs.

// Test_Case
constexpr Or<Rain, Wet, true> part4_l = or_left<Wet>(axiom_rain());
constexpr Or<Rain, Wet, false> part4_r = or_right<Rain>(axiom_wet());

static_assert(
    std::is_same_v<std::remove_const_t<decltype(part4_l.proof)>, Rain>);
static_assert(
    std::is_same_v<std::remove_const_t<decltype(part4_r.proof)>, Wet>);

// Or<Rain,Contradiction,true> is well-formed: Contradiction is never
// constructed
constexpr Or<Rain, Contradiction, true> part4_safe =
    or_left<Contradiction>(axiom_rain());
static_assert(
    std::is_same_v<std::remove_const_t<decltype(part4_safe.proof)>, Rain>);

// ============================================================================
// PART 5: Negation - NOT
// ============================================================================

// Not<P> means: given a proof of P, we can derive Contradiction.
// A proof of Not<P> is any callable F satisfying Proves<F, P, Contradiction>.
//
// We define ProvesNot<F,P> as shorthand for this.
//
// Since Contradiction() is deleted, such a callable can never actually
// be called with a real argument, but it can exist purely as a type and it
// therefore satisfies the concept.
// TODO: Define ProvesNot concept to as Proves<F, P, Contradiction>

// Test_Case
static_assert(
    ProvesNot<decltype([](Cold) -> Contradiction { throw 0; }), Cold>);
static_assert(!ProvesNot<decltype([](Cold) -> Rain { return {}; }), Cold>);

// ============================================================================
// PART 6: Proposition inspection
// ============================================================================

// Using partial template specialization we can inspect the structure
// of a proposition at compile time without constructing any values.
//
// TODO: Define structs:
//   - IsAnd<T> value = true iff T is And<P,Q> for some P, Q;
//   otherwise value = false
//   - IsOr<T>  value = true iff T is Or<P,Q,B> for some P, Q, B;
//   otherwise value = false
// i.e.
// Generic case: value = false
// Specialized case: value = true

// TODO: define IsAnd, IsOr here

// Test_Case
static_assert(IsAnd<And<Rain, Wet>>::value);
static_assert(!IsAnd<Rain>::value);
static_assert(!IsAnd<Or<Rain, Wet, true>>::value);

static_assert(IsOr<Or<Rain, Wet, true>>::value);
static_assert(IsOr<Or<Rain, Wet, false>>::value);
static_assert(!IsOr<Rain>::value);
static_assert(!IsOr<And<Rain, Wet>>::value);

// ============================================================================
// PART 7: Theorem - And<P,Q> => And<Q,P>
// ============================================================================

// Prove: And<P,Q> => And<Q,P>
// "Conjunction is commutative."
//
// A theorem is a constexpr function that returns a lambda.
// The lambda IS the proof, as its type satisfies Proves.
//
// TODO: Implement a constexpr function 'theorem_and_commutative()' that:
//    - takes 2 template typenames P and Q
//    - returns a lambda And<P,Q> -> And<Q,P> (takes And<P,Q>, returns And<Q,P>)
// Hint: use and_left, and_right, and prove_and

static_assert(Proves<decltype(theorem_and_commutative<Rain, Wet>()),
                     And<Rain, Wet>, And<Wet, Rain>>);

constexpr And<Rain, Wet> part7_premise = prove_and(axiom_rain(), axiom_wet());
constexpr And<Wet, Rain> part7_conclusion =
    apply(theorem_and_commutative<Rain, Wet>(), part7_premise);
static_assert(std::is_same_v<std::remove_const_t<decltype(part7_conclusion)>,
                             And<Wet, Rain>>);

// ============================================================================
// PART 8: Compose - chaining implications
// ============================================================================

// If F proves P => Q and G proves Q => R, then compose(f,g) proves P => R.
// This is function composition applied to proofs.
//
//
// TODO: Implement constexpr function 'compose(F f, G g)':
//   - return-type auto
//   - takes 2 template typename args F and G
//   - returns a lambda that captures f and g, and takes an auto argument p;
//   then chaining the call of g on f of p.
//
// NOTE: compose takes only F and G as template parameters. P, Q, R are
// deduced from the lambda body using auto. This avoids deduction failures
// that arise when trying to extract P, Q, R from the callable types F and G.

// TODO: define compose here

constexpr auto part8_rain_to_wet = [](Rain) { return Wet{}; };
constexpr auto part8_wet_to_cold = [](Wet) { return Cold{}; };
constexpr auto part8_rain_to_cold =
    compose(part8_rain_to_wet, part8_wet_to_cold);

static_assert(Proves<decltype(part8_rain_to_cold), Rain, Cold>);

constexpr Cold part8_conclusion = apply(part8_rain_to_cold, axiom_rain());
static_assert(
    std::is_same_v<std::remove_const_t<decltype(part8_conclusion)>, Cold>);

// ============================================================================
// PART 9: Theorem - And<P,And<Q,R>> => And<And<P,Q>,R>
// ============================================================================

// Prove: And<P,And<Q,R>> => And<And<P,Q>,R>
// "Conjunction is associative."
//
// This requires unpacking the nested And and repacking in a different order.
// The types guide the proof. If you extract in the wrong order the
// compiler rejects it.
//
// TODO: Implement a constexpr function theorem_and_assoc():
//  - return-type auto
//  - takes 3 template typename P, Q, R
//  - returns a lambda And<P,And<Q,R>> -> And<And<P,Q>,R>
// Hint: extract p, qr, q, r separately then repack

static_assert(Proves<decltype(theorem_and_assoc<Rain, Wet, Cold>()),
                     And<Rain, And<Wet, Cold>>, And<And<Rain, Wet>, Cold>>);

constexpr And<Rain, And<Wet, Cold>> part9_premise =
    prove_and(axiom_rain(), prove_and(axiom_wet(), axiom_cold()));
constexpr And<And<Rain, Wet>, Cold> part9_conclusion =
    apply(theorem_and_assoc<Rain, Wet, Cold>(), part9_premise);
static_assert(std::is_same_v<std::remove_const_t<decltype(part9_conclusion)>,
                             And<And<Rain, Wet>, Cold>>);

// ============================================================================
// PART 10: Theorem — Contrapositive
// ============================================================================

// TODO: Prove: (P => Q) => (Not<Q> => Not<P>)
// "If P implies Q, then any disproof of Q disproves P."
//
// In our encoding:
//   f : proves P => Q    any callable P -> Q
//   g : proves Not<Q>    any callable Q -> Contradiction
//   h : proves Not<P>    the callable P -> Contradiction
//   where h(p) = g(f(p))
//
// The proof is three nested lambdas; one for each implication:
//   outer:  takes f (proof of P => Q)
//   middle: takes g (proof of Not<Q>)
//   inner:  takes p (proof of P), returns g(f(p)) : Contradiction
//
// The inner lambda captures f and g naturally.
// No std::function is needed because lambdas already capture state.
// This is only possible because theorems are generic callables —
// not wrapped function pointers.
//
// TODO: Implement constexpr 'theorem_contrapositive()':
//    - return-type auto
//    - takes 2 template typenames P and Q
//    - returns a lambda that takes any f proving P => Q;
//     and returns a lambda that takes any g proving Not<Q>;
//     and returns a lambda P -> Contradiction
//     where the innermost body is: return g(f(p))

// TODO: define theorem_contrapositive here

constexpr auto part10_thm = theorem_contrapositive<Rain, Wet>();
constexpr auto part10_f = [](Rain) -> Wet { return {}; };
constexpr auto part10_cp = apply(part10_thm, part10_f);
constexpr auto part10_nw = [](Wet) -> Contradiction { throw 0; };
constexpr auto part10_nr = apply(part10_cp, part10_nw);

static_assert(ProvesNot<decltype(part10_nr), Rain>);

// ============================================================================
// OPTIONAL: De Morgan's Law
// ============================================================================
//
// Prove: Or<NP,NQ,IsLeft> => Not<And<P,Q>>
// where NP satisfies ProvesNot<NP,P> and NQ satisfies ProvesNot<NQ,Q>
//
// "If P is false or Q is false, then P and Q is false."
//
// This is the constructively provable direction of De Morgan's law.
// The other direction requires the Law of Excluded Middle, which is
// not available in constructive logic — the logic Curry-Howard
// corresponds to. This is a genuine result from proof theory.
//
// Because Or<P,Q,IsLeft> encodes which side was proved in the type,
// De Morgan splits naturally into 2 overloads dispatched by the
// compiler at compile time — no runtime branching needed:
//
//   // Case: left side proved (NP : P -> Contradiction)
//   template<typename P, typename Q, typename NP, typename NQ>
//   requires ProvesNot<NP,P>
//   constexpr auto theorem_demorgan(Or<NP,NQ,true> o) {
//       NP not_p = o.proof;
//       return [not_p](And<P,Q> a) -> Contradiction {
//           return not_p(and_left(a));
//       };
//   }
//
//   // Case: right side proved (NQ : Q -> Contradiction)
//   template<typename P, typename Q, typename NP, typename NQ>
//   requires ProvesNot<NQ,Q>
//   constexpr auto theorem_demorgan(Or<NP,NQ,false> o) {
//       NQ not_q = o.proof;
//       return [not_q](And<P,Q> a) -> Contradiction {
//           return not_q(and_right(a));
//       };
//   }
//
