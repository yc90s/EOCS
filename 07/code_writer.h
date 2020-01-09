#ifndef __CODE_WRITER_H__
#define __CODE_WRITER_H__

#include <string>
#include <fstream>
#include <unordered_map>

struct CommandArgs
{
    std::string segment;
    int         index;
};

// hardware platform related
class CodeWriter
{
//    typedef bool(CodeWriter::*OpCodeFunc)(CommandArgs const&);
    using OpCodeFunc = bool(CodeWriter::*)(CommandArgs const&);
    using TranslateSegmentFunc = void(CodeWriter::*)(CommandArgs const&);
    public:
        CodeWriter(const std::string& output_file);
        virtual ~CodeWriter();
        CodeWriter(const CodeWriter&) = delete;
        CodeWriter& operator= (const CodeWriter&) = delete;

    public:
        // translate new vm file
        void set_file_name(const std::string& filename);

        bool write_arithmetic(const std::string& command);
        bool write_push_pop(const std::string& opcode, const std::string& segment, int index);

    protected:
        virtual bool op_add(CommandArgs const&) = 0;
        virtual bool op_sub(CommandArgs const&) = 0;
        virtual bool op_neg(CommandArgs const&) = 0;
        virtual bool op_eq(CommandArgs const&) = 0;
        virtual bool op_gt(CommandArgs const&) = 0;
        virtual bool op_lt(CommandArgs const&) = 0;
        virtual bool op_and(CommandArgs const&) = 0;
        virtual bool op_or(CommandArgs const&) = 0;
        virtual bool op_not(CommandArgs const&) = 0;
        virtual bool op_push(CommandArgs const&) = 0;
        virtual bool op_pop(CommandArgs const&)= 0;

    protected:
        bool translate_segment(CommandArgs const&);
        void translate_argument(CommandArgs const&);
        void translate_local(CommandArgs const&);
        void translate_static(CommandArgs const&);
        void translate_constant(CommandArgs const&);
        void translate_this(CommandArgs const&);
        void translate_that(CommandArgs const&);
        void translate_pointer(CommandArgs const&);
        void translate_temp(CommandArgs const&);

    protected:
        std::fstream    fs_;
        std::string     curr_vm_file_name_;
        unsigned int    branch_label_no_;
        unsigned int    continue_label_no_;
        static std::unordered_map<std::string, OpCodeFunc>      optables_;
        static std::unordered_map<std::string, TranslateSegmentFunc> translate_segment_tables_;
};

class HackCodeWriter : public CodeWriter
{
    public:
        HackCodeWriter(const std::string&);
        ~HackCodeWriter() = default;
        HackCodeWriter(const HackCodeWriter&) = delete;
        HackCodeWriter& operator= (const HackCodeWriter&) = delete;

    protected:
        bool op_add(CommandArgs const&) override;
        bool op_sub(CommandArgs const&) override;
        bool op_neg(CommandArgs const&) override;
        bool op_eq(CommandArgs const&) override;
        bool op_gt(CommandArgs const&) override;
        bool op_lt(CommandArgs const&) override;
        bool op_and(CommandArgs const&) override;
        bool op_or(CommandArgs const&) override;
        bool op_not(CommandArgs const&) override;
        bool op_push(CommandArgs const&) override;
        bool op_pop(CommandArgs const&)override;
};

#endif 
