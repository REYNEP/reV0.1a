## BackStory [before `C++0x`]
- https://www.youtube.com/watch?v=I-hZkUa9mIs
- https://www.youtube.com/watch?v=j0_u26Vpb4w
- https://www.youtube.com/watch?v=-AQfQFcXac8 [😉 take a break smtimes]

## A RoadMap
- https://github.com/salmer/CppDeveloperRoadmap [Has a Miro/GraphML]
- RoadMap also features this:- https://github.com/AnthonyCalandra/modern-cpp-features

## Okay RightNow, this is me, Change my Mind :)
- https://www.youtube.com/watch?v=Z_ahq2h9Xxg

## OAKY
#### Okay, soooo, you are an algorithm artist.... you really don't gotta care about _'Template-izing'_ you know.... thats simply not your job >_< + nor do you need to care about stuff like move_semantics or stuff like that.... czzzz thats the basics of algo yk

















</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
</br>
---
---
---
---
---
---

## My Take on `MoveSemantics`
- Imagine you are in the 90s, But you have CLASS, and you wanna *COPY* an `String`
  1. Assume string has some HeapMemory associated with it
    1.1 So *COPY* means `malloc + memcpy`
      - Some would prefer the term 'DeepCopy'
      - Some would prefer modern C++ techniques rather than using `malloc + memcpy`
      - so, This Copy has a cost [tooMuch `O(N)`] </br></br>
  2. Let' also assume, after a while, you encounter a new kinda case
    2.1 You only need variable `B` to _'hold'_ what `A` was holding
      - Some would prefer the term 'ShallowCopy'
      - WHY? maybe `B` is like `MSGLast` and `A` is `MSGNow`
      - e.g. maybe the user might be looking for LastMessage/Log/State </br></br>

- Okay, so How do we solve this now 🤔 .... _Intuition time_
  1. If we are allowed to assume, `String` holds `char *ptrToHeap`
    1.1 then we can just do `B.ptrToHeap = A.ptrToHeap;`
      - (maybe `String` had only 1 more member, `m_size`) 😜 </br></br>
  2. Well, what we are doing above is just the _'Default Copy Constructor/AssignmentOperator'_ that the compiler gives us
    2.1 e.g. `String B = A; //CopyConstructor`
      - (personally I can't stand it when people calls it _'Ctor'_ 😖)
      - if we did `B = A; //CopyAssignmentOperator` would be called
      - `String& String::operator=(const String&) = default;`
      - imma call this _'CopyByValue'_ </br></br>

- Now one last problem remains.... and that is
  1. Both `A` and `B` is now pointing to the same HeapMemory
  2. SO, if we assume that `Struct::~Struct()` actually `free()`s or `delete`s the memory....
    2.1 we'd always need to keep setting back `A` back to **NIL** values
  3. So What I propose is the use of `Create()` & `Destroy()`
    3.0 `Destroy()` now calls `free()`
    3.1 This is the `C` way to do stuff .... 😣
      - I know there are people who hates those.... But
      - but but, even the Vulkan Official Headers come in those format
      - (yeah, Iknow that those don't use Classes or whatever, but still) </br></br>

- Now to SUMMERIZE
  1. We don't care about CONSTRUCTOR, it's default given by Compiler.
  2. We don't care about DESTRUCTOR,  it's default given by Compiler.
  3. We don't care about CopyAssignmentOperator or CopyConstructor....
  4. But, Wed care about ... `Create()`
  5. And, Wed care about ... `Destroy()`
    5.1. so we only gotta care about 2 things....
      - 🤔 maybe a `CopyTo()` function too
      - but the good thing now is, we don't gotta care about that untill....
      - the class `Struct` hold some other class, which we'd not wanna _'CopyByValue'_
  6. Soooo, we End up with no kinda HeadAche....
  7. Till 2023, Blender's GHOST (GenericHandyOperatingSystemToolkit) uses this convention.... And I really did like this way....
---
- Now if you get into Move-Semantics....
  1. https://www.youtube.com/watch?v=fbYknr-HPYE
  2. https://www.youtube.com/watch?v=ehMg6zvXuMY
  3. https://www.youtube.com/watch?v=OWNeCTd7yQE
  4. Notice that all of a sudden you gotta care about
     - Constructor
     - Destructor
     - CopyAssignmentOperator
     - CopyConstructor
     - MoveAssignmentOperator
     - MoveConstructor
     - Also you gotta keep using `std::move`
       - well uhh, you can also do `B = (String &&)A;`
       - yes, all that it implies now is that.... Instead of all these operators.... there could have been just plain old functions >_<
       - e.g. `ShallowCopy` or `Move_DontCopy`
       - Imply-ing these simple transitions into newer/better Guides/StyleGuides would have been far better than making `std::move` the standard way to do stuff >_<
       - like I just hate it that, because its now standard, most people are gonna keep using it.... and we (newbs) lost the freedom to come up with their very own solution (using funcs like `ShallowCopy`) to this >_<
       - I am not rude or raged up.... I just think that.... It kinda becomes their ***Responsibility*** (_'With Great Power, comes Great Responsibility'_) to write up a Procedural Teaching guide on al' of these 6 functions.... and moveSemantics in general.... where student would be encouraged to come up with their very own fkin solution instead of just THROWING out some ***Knowledge*** or ***Standard Conventions*** or whatever at them.... just Like in CS50
       - honestly i think introducing `move` keyword like `new` keyword would have been better choice </br></br>

- you know honestly.... the more I'm getting introduced to these rules to play by
  1. I'm realising that.... people are just introducing most of these out of fear.... rather than originating from making life 'simple'
  2. Like first they introduced stuff like `std::vector` and `std::map`
    2.1 then they noticed like, most of the people assumed imaginary powers of these.... like automatically cleaning up resources (as in from HEAPs)
    2.2 e.g. _'bad use of `new` and `delete`'_
    2.3 yes, this happens cause.... people from all kinds of languages comes here.... >_< and I totally understand the C++ stuff are just trynna create compatible conventions for those people who are coming from some higher level language
  3. Most of these rules are stupid.... and doesn't really apply to me.... I'm not that stupid person, _at least not that much to even make misuse/mistakes like that with pointers or memory allocations or leaks_ 😔
  4. like, uhhhh.... people usually doesn't advice to use labels....
    4.1 to understand what I'm sayin, please go watch that 2nd Video at first _'Backstory'_ section....
    4.2 they explain the reason like _'code can like spaghetti'_
    4.3 well you know, you can literally see with your 👀 (🙄) when smth like that's happening.... (i mean, you can literally see and tell if its not the right way to use `goto` >_<)
    4.4 In the video, an okay/acceptable case is showed or talked about....
    4.5 honestly I never even thought that.... `goto` should/can be used for other than that _'okay'_ case.... like why the heck would someone actually wanna make their code spaghetti.... i never even considered, human's brains could go brrrrrrrrr to do thaaaaaat.
  5. People are just afraid of Pointers, they don't really wanna worry in terms of Pointers.... they'd rather worry in terms of _'References'_ thus the new ways & stuff....
    5.1 This isn't necessarily bad, but i think the extra extra usage of CopyConstructor or Copy/MoveAssignment Operator isn't that fancy or cool!
  6. I hate Variadic templates.... but since its Compile Time stuff.... >_< gotta appreciate the Performance benefits
  7. I hate Smart Pointers.... I am not afraid of Pointers and Resource management.... >_<
