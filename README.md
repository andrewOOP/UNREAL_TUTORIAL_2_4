# UNREAL_TUTORIAL_2_4

# BROKEN
Turns out, this tutorial was removed from Unreal's main website for a reason, it's OLD.
I followed the tutorial, but it wasn't working, so I got the tutorial's source files and tried to work it in that way.
After a ton of includes and code fixes, I still couldn't get it to work. Heck, even the downloadable "finished project files" don't work.

Maybe if I just had bad luck trying to get their code in?
But with how much needs to be fixed for the latest updates like...

* Outside includes shouldn't be in the header file, only in cpp
* Everything must be included, nothing is included by default anymore
* Making a private variable just to use meta to make it writeable is dumb
* So many false errors it hurts
* This won't work: static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
No matter what I try, it just won't work and throws me an error saying it can't find it
  
Anyway, I say forget this tutorial. The rest of the tutorials in Round 2 were good.
