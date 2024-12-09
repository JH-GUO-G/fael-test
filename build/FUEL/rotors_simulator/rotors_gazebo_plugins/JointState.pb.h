// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: JointState.proto

#ifndef PROTOBUF_INCLUDED_JointState_2eproto
#define PROTOBUF_INCLUDED_JointState_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "Header.pb.h"
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_JointState_2eproto 

namespace protobuf_JointState_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_JointState_2eproto
namespace gz_sensor_msgs {
class JointState;
class JointStateDefaultTypeInternal;
extern JointStateDefaultTypeInternal _JointState_default_instance_;
}  // namespace gz_sensor_msgs
namespace google {
namespace protobuf {
template<> ::gz_sensor_msgs::JointState* Arena::CreateMaybeMessage<::gz_sensor_msgs::JointState>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace gz_sensor_msgs {

// ===================================================================

class JointState : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:gz_sensor_msgs.JointState) */ {
 public:
  JointState();
  virtual ~JointState();

  JointState(const JointState& from);

  inline JointState& operator=(const JointState& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  JointState(JointState&& from) noexcept
    : JointState() {
    *this = ::std::move(from);
  }

  inline JointState& operator=(JointState&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const JointState& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const JointState* internal_default_instance() {
    return reinterpret_cast<const JointState*>(
               &_JointState_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(JointState* other);
  friend void swap(JointState& a, JointState& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline JointState* New() const final {
    return CreateMaybeMessage<JointState>(NULL);
  }

  JointState* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<JointState>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const JointState& from);
  void MergeFrom(const JointState& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(JointState* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated string name = 2;
  int name_size() const;
  void clear_name();
  static const int kNameFieldNumber = 2;
  const ::std::string& name(int index) const;
  ::std::string* mutable_name(int index);
  void set_name(int index, const ::std::string& value);
  #if LANG_CXX11
  void set_name(int index, ::std::string&& value);
  #endif
  void set_name(int index, const char* value);
  void set_name(int index, const char* value, size_t size);
  ::std::string* add_name();
  void add_name(const ::std::string& value);
  #if LANG_CXX11
  void add_name(::std::string&& value);
  #endif
  void add_name(const char* value);
  void add_name(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField< ::std::string>& name() const;
  ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_name();

  // repeated double position = 3 [packed = true];
  int position_size() const;
  void clear_position();
  static const int kPositionFieldNumber = 3;
  double position(int index) const;
  void set_position(int index, double value);
  void add_position(double value);
  const ::google::protobuf::RepeatedField< double >&
      position() const;
  ::google::protobuf::RepeatedField< double >*
      mutable_position();

  // required .gz_std_msgs.Header header = 1;
  bool has_header() const;
  void clear_header();
  static const int kHeaderFieldNumber = 1;
  private:
  const ::gz_std_msgs::Header& _internal_header() const;
  public:
  const ::gz_std_msgs::Header& header() const;
  ::gz_std_msgs::Header* release_header();
  ::gz_std_msgs::Header* mutable_header();
  void set_allocated_header(::gz_std_msgs::Header* header);

  // @@protoc_insertion_point(class_scope:gz_sensor_msgs.JointState)
 private:
  void set_has_header();
  void clear_has_header();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::std::string> name_;
  ::google::protobuf::RepeatedField< double > position_;
  mutable int _position_cached_byte_size_;
  ::gz_std_msgs::Header* header_;
  friend struct ::protobuf_JointState_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// JointState

// required .gz_std_msgs.Header header = 1;
inline bool JointState::has_header() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void JointState::set_has_header() {
  _has_bits_[0] |= 0x00000001u;
}
inline void JointState::clear_has_header() {
  _has_bits_[0] &= ~0x00000001u;
}
inline const ::gz_std_msgs::Header& JointState::_internal_header() const {
  return *header_;
}
inline const ::gz_std_msgs::Header& JointState::header() const {
  const ::gz_std_msgs::Header* p = header_;
  // @@protoc_insertion_point(field_get:gz_sensor_msgs.JointState.header)
  return p != NULL ? *p : *reinterpret_cast<const ::gz_std_msgs::Header*>(
      &::gz_std_msgs::_Header_default_instance_);
}
inline ::gz_std_msgs::Header* JointState::release_header() {
  // @@protoc_insertion_point(field_release:gz_sensor_msgs.JointState.header)
  clear_has_header();
  ::gz_std_msgs::Header* temp = header_;
  header_ = NULL;
  return temp;
}
inline ::gz_std_msgs::Header* JointState::mutable_header() {
  set_has_header();
  if (header_ == NULL) {
    auto* p = CreateMaybeMessage<::gz_std_msgs::Header>(GetArenaNoVirtual());
    header_ = p;
  }
  // @@protoc_insertion_point(field_mutable:gz_sensor_msgs.JointState.header)
  return header_;
}
inline void JointState::set_allocated_header(::gz_std_msgs::Header* header) {
  ::google::protobuf::Arena* message_arena = GetArenaNoVirtual();
  if (message_arena == NULL) {
    delete reinterpret_cast< ::google::protobuf::MessageLite*>(header_);
  }
  if (header) {
    ::google::protobuf::Arena* submessage_arena = NULL;
    if (message_arena != submessage_arena) {
      header = ::google::protobuf::internal::GetOwnedMessage(
          message_arena, header, submessage_arena);
    }
    set_has_header();
  } else {
    clear_has_header();
  }
  header_ = header;
  // @@protoc_insertion_point(field_set_allocated:gz_sensor_msgs.JointState.header)
}

// repeated string name = 2;
inline int JointState::name_size() const {
  return name_.size();
}
inline void JointState::clear_name() {
  name_.Clear();
}
inline const ::std::string& JointState::name(int index) const {
  // @@protoc_insertion_point(field_get:gz_sensor_msgs.JointState.name)
  return name_.Get(index);
}
inline ::std::string* JointState::mutable_name(int index) {
  // @@protoc_insertion_point(field_mutable:gz_sensor_msgs.JointState.name)
  return name_.Mutable(index);
}
inline void JointState::set_name(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:gz_sensor_msgs.JointState.name)
  name_.Mutable(index)->assign(value);
}
#if LANG_CXX11
inline void JointState::set_name(int index, ::std::string&& value) {
  // @@protoc_insertion_point(field_set:gz_sensor_msgs.JointState.name)
  name_.Mutable(index)->assign(std::move(value));
}
#endif
inline void JointState::set_name(int index, const char* value) {
  GOOGLE_DCHECK(value != NULL);
  name_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:gz_sensor_msgs.JointState.name)
}
inline void JointState::set_name(int index, const char* value, size_t size) {
  name_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:gz_sensor_msgs.JointState.name)
}
inline ::std::string* JointState::add_name() {
  // @@protoc_insertion_point(field_add_mutable:gz_sensor_msgs.JointState.name)
  return name_.Add();
}
inline void JointState::add_name(const ::std::string& value) {
  name_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:gz_sensor_msgs.JointState.name)
}
#if LANG_CXX11
inline void JointState::add_name(::std::string&& value) {
  name_.Add(std::move(value));
  // @@protoc_insertion_point(field_add:gz_sensor_msgs.JointState.name)
}
#endif
inline void JointState::add_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  name_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:gz_sensor_msgs.JointState.name)
}
inline void JointState::add_name(const char* value, size_t size) {
  name_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:gz_sensor_msgs.JointState.name)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
JointState::name() const {
  // @@protoc_insertion_point(field_list:gz_sensor_msgs.JointState.name)
  return name_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
JointState::mutable_name() {
  // @@protoc_insertion_point(field_mutable_list:gz_sensor_msgs.JointState.name)
  return &name_;
}

// repeated double position = 3 [packed = true];
inline int JointState::position_size() const {
  return position_.size();
}
inline void JointState::clear_position() {
  position_.Clear();
}
inline double JointState::position(int index) const {
  // @@protoc_insertion_point(field_get:gz_sensor_msgs.JointState.position)
  return position_.Get(index);
}
inline void JointState::set_position(int index, double value) {
  position_.Set(index, value);
  // @@protoc_insertion_point(field_set:gz_sensor_msgs.JointState.position)
}
inline void JointState::add_position(double value) {
  position_.Add(value);
  // @@protoc_insertion_point(field_add:gz_sensor_msgs.JointState.position)
}
inline const ::google::protobuf::RepeatedField< double >&
JointState::position() const {
  // @@protoc_insertion_point(field_list:gz_sensor_msgs.JointState.position)
  return position_;
}
inline ::google::protobuf::RepeatedField< double >*
JointState::mutable_position() {
  // @@protoc_insertion_point(field_mutable_list:gz_sensor_msgs.JointState.position)
  return &position_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace gz_sensor_msgs

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_JointState_2eproto