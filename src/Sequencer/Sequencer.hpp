//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include "Ensemble.h"
#include "DotGrid.h"
#include "Cursor.h"

class Sequencer: public UIComponent, public ClockListener
{
public:
    Sequencer();
    Sequencer(int x, int y, int width, int height);
    ~Sequencer();

public:
    void draw() override;
    void setPositionWithOrigin(const int x, const int y) override;
    void setPositionWithCentre(const int x, const int y) override;
    void setSizeFromCentre(const float width, const float height) override;
    void setSize(const float width, const float height) override;
    void setMargins(const int top, const int left, const int right, const int bottom) override;
    [[nodiscard]] const UIMargins<int>& getMargins() const noexcept override;

public:
    void tick() override;
    void toggleClock() noexcept;
    
public:
    /// @brief Return a textual description of the sequencer's contents at the cursor's current position.

    inline std::string_view getHoverDescription() noexcept
    {
        return hoverDescription;
    }

public:
    void moveCursor(Direction direction) noexcept;
    void moveCursorToScreenPosition(const int x, const int y) noexcept;
    void setCursorOctave(const int octave) noexcept;
    
public:
    /// @brief Place a new note at the sequencer cursor's current position.
    /// @param noteIndex A number in the range [0, 11] representing a note from the chromatic scale, beginning with C.
    /// @return A Boolean value to indicate whether the note was placed successfully or not.
    /// @throw An exception will be thrown in the case where the given position is out of range.

    bool placeNote(uint8_t noteIndex) noexcept(false);
    
    /// @brief Place a new portal node at the sequencer cursor's current position.
    /// @return A Boolean value to indicate whether the node was placed successfully or not.
    /// @throw An exception will be thrown in the case where the given position is out of range.
    
    bool placePortal() noexcept(false);
    
    /// @brief Place a new redirect node at the sequencer cursor's current position.
    /// @param type The desired type of redirect node to place.
    /// @return A Boolean value to indicate whether the node was placed successfully or not.
    /// @throw An exception will be thrown in the case where the given position is out of range.

    bool placeRedirect(Redirection type) noexcept(false);
    
    /// @brief Place a new playhead at the sequencer cursor's current position.
    /// @param direction The desired direction of the playhead node.

    void placePlayhead(Direction direction) noexcept;

    /// @brief Erase the contents of the sequencer at the sequencer cursor's current position.
    /// @throw An exception will be thrown in the case where the given position is out of range.

    void eraseFromCurrentPosition() noexcept(false);

private:
    /// @brief Update the underlying data structures to reflect a change in the size of the sequencer grid.

    void gridDimensionsDidUpdate() noexcept(false);
    
    /// @brief Update the string that describes the contents of the sequencer at the cursor's current position.

    void updateHoverDescriptionString() noexcept;

private:
    Clock      clock;
    Cursor     cursor;
    DotGrid    grid;
    MIDIServer midiServer;
    
private:
    /// @brief A textual description of the sequence's contents at the cursor's current position.

    std::string hoverDescription;
    
private:
    std::vector<SQPlayhead> playheads;
    std::vector<SQPortal *> unpairedPortals;
    
    Table<std::shared_ptr<SQNode>> table;
};

#endif
