#pragma once

#include "KeyboardManager.h"

#include <unordered_set>
#include <unordered_map>
#include <string>


#define LOG_CONTROLLER(CONTROLLER, FORMAT, ...)                                                                 \
    LOG ( "%s: controller=%08x; joystick=%08x; state=%08x; " FORMAT,                                            \
          CONTROLLER->getName(), CONTROLLER, CONTROLLER->joystick, CONTROLLER->state, ## __VA_ARGS__ )


#define BIT_UP          ( 0x00000001u )
#define BIT_DOWN        ( 0x00000002u )
#define BIT_LEFT        ( 0x00000004u )
#define BIT_RIGHT       ( 0x00000008u )

#define MASK_X_AXIS     ( 0x0000000Cu )
#define MASK_Y_AXIS     ( 0x00000003u )
#define MASK_DIRS       ( 0x0000000Fu )
#define MASK_BUTTONS    ( 0xFFFFFFF0u )


// Forward declarations
struct _SDL_Joystick;
typedef struct _SDL_Joystick SDL_Joystick;
struct SDL_JoyAxisEvent;
struct SDL_JoyHatEvent;
struct SDL_JoyButtonEvent;


struct KeyboardMappings : public SerializableSequence
{
    // Controller unique identifier
    std::string name;

    // bit index -> virtual key code
    uint32_t codes[32];

    // bit index -> key name
    std::string names[32];

    PROTOCOL_MESSAGE_BOILERPLATE ( KeyboardMappings, name, codes, names )
};


struct JoystickMappings : public SerializableSequence
{
    // Controller unique identifier
    std::string name;

    // event type -> axis/hat/button index -> axis/hat/button value -> mapped key
    //
    // The neutral axis/hat/button value is mapped to a bit mask of all the mapped values on the same index.
    //
    // Example:                                         Example:
    //   Axis up      -> 0b0001                           Hat up      -> 0b0001   Hat left  -> 0b0100
    //   Axis down    -> 0b0010                           Hat down    -> 0b0010   Hat right -> 0b1000
    //
    // Then:                                            Then:
    //   Axis neutral -> 0b0011                           Hat neutral -> 0b1111
    //
    uint32_t mappings[3][256][16];

    // Find a 3-tuple mapping for the given key, returns false if none exist
    bool find ( uint32_t key, uint8_t& type, uint8_t& index, uint8_t& value ) const
    {
        for ( uint8_t i = 0; i < 3; ++i )
        {
            for ( uint16_t j = 0; j < 256; ++j )
            {
                for ( uint8_t k = 1; k < 16; ++k ) // We skip value=0 since it is the neutral value
                {
                    if ( mappings[i][j][k] == key )
                    {
                        type = i;
                        index = j;
                        value = k;
                        return true;
                    }
                }
            }
        }

        return false;
    }

    PROTOCOL_MESSAGE_BOILERPLATE ( JoystickMappings, name, mappings )
};


class Controller : public KeyboardManager::Owner
{
public:

    struct Owner
    {
        virtual void doneMapping ( Controller *controller, uint32_t key ) = 0;
    };

    Owner *owner = 0;

private:

    // Enum type for keyboard controller
    enum KeyboardEnum { Keyboard };

    // Original controller name
    const std::string name;

    // SDL joystick pointer, 0 for keyboard
    SDL_Joystick *joystick = 0;

    // Controller state
    uint32_t state = 0;

    // Keyboard mappings
    KeyboardMappings keybd;

    // Joystick mappings
    JoystickMappings stick;

    // The current key to map to an event
    uint32_t keyToMap = 0;

    // The currently active joystick mappings for the above key
    JoystickMappings active;

    // Keyboard event callback
    void keyboardEvent ( uint32_t vkCode, uint32_t scanCode, bool isExtended, bool isDown );

    // Joystick event callbacks
    void joystickEvent ( const SDL_JoyAxisEvent& event );
    void joystickEvent ( const SDL_JoyHatEvent& event );
    void joystickEvent ( const SDL_JoyButtonEvent& event );

    // Construct a keyboard / joystick controller
    Controller ( KeyboardEnum );
    Controller ( SDL_Joystick *joystick );

public:

    // Joystick axis deadzones
    uint16_t deadzones[256];

    // Basic destructor
    ~Controller();

    // Get controller name with index
    const std::string& getName() const
    {
        if ( isKeyboard() )
            return keybd.name;
        else
            return stick.name;
    }

    // Indicates if this is the only controller with its original name
    bool isUniqueName() const;

    // Get the mapping for the given key as a human-readable string
    std::string getMapping ( uint32_t key ) const;

    // Get the mappings for this controller
    MsgPtr getMappings() const
    {
        if ( isKeyboard() )
            return keybd.clone();
        else
            return stick.clone();
    }

    // Set the mappings for this controller
    void setMappings ( const KeyboardMappings& mappings ) { keybd = mappings; }
    void setMappings ( const JoystickMappings& mappings ) { stick = mappings; }

    // Start / cancel mapping for the given key
    void startMapping ( Owner *owner, uint32_t key, const void *window = 0 );
    void cancelMapping();

    // Clear this controller's mapping(s)
    void clearMapping ( uint32_t keys = 0xFFFFFFFF );

    // Get the controller state
    uint32_t getState() const { return state; }

    // Indicates if this is a keyboard / joystick controller
    bool isKeyboard() const { return ( joystick == 0 ); }
    bool isJoystick() const { return ( joystick != 0 ); }

    // Save / load mappings for this controller
    bool saveMappings ( const std::string& file ) const;
    bool loadMappings ( const std::string& file );

    friend class ControllerManager;
};
