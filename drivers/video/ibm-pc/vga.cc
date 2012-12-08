#include <drivers/video/ibm-pc/vga.hh>

namespace platform
{
    Vga& Vga::instance()
    {
        static Vga instance_;

        return instance_;
    }

    Vga::Vga()
      : modifier_(MODIFIER_WHITE)
    {
    }

    Vga::Vga(const Vga&)
    {
    }
    
    void Vga::set_mode(mode_e m)
    {
        mode_ = m;
    }

    void Vga::clear()
    {
        switch (mode_)
        {
            case MODE_TEXT_80x25:
            {
                for (unsigned int i = 0; i < 80 * 25; ++i)
                    buffer_text_80x25[i].ch = 0;
                break;
            }

            default:
                break;
        }
    }

    void Vga::set_modifier(modifier_e m)
    {
        modifier_ = m;
    }

    void Vga::set_cursor(unsigned int row, unsigned int col)
    {
        // FIXME
    }

    void Vga::put(unsigned int row, unsigned int col, char c)
    {
        buffer_char_t buffer_char;

        if (mode_ != MODE_TEXT_80x25)
            return;

        // TODO: Handle invalid row / col
        //if ((row) && (col))

        buffer_char.ch = c;
        buffer_char.fg = modifier_;
        buffer_char.bg = 0;

        Vga::put(row, col, buffer_char);
    }

    void Vga::put(unsigned int row, unsigned int col, buffer_char_t c)
    {
        buffer_text_80x25[row * 80 + col] = c;
    }
}