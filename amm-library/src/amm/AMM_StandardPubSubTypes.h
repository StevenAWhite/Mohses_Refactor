// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file AMM_StandardPubSubTypes.h
 * This header file contains the declaration of the serialization functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#ifndef _FAST_DDS_GENERATED_AMM_AMM_STANDARD_PUBSUBTYPES_H_
#define _FAST_DDS_GENERATED_AMM_AMM_STANDARD_PUBSUBTYPES_H_

#include <fastdds/dds/topic/TopicDataType.hpp>
#include <fastrtps/utils/md5.h>

#include "AMM_Standard.h"

#if !defined(GEN_API_VER) || (GEN_API_VER != 1)
#error \
    Generated AMM_Standard is not compatible with current installed Fast DDS. Please, regenerate it with fastddsgen.
#endif  // GEN_API_VER

namespace AMM
{
    /*!
     * @brief This class represents the TopicDataType of the type FMA_Location defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class FMA_LocationPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef FMA_Location type;

        eProsima_user_DllExport FMA_LocationPubSubType();

        eProsima_user_DllExport virtual ~FMA_LocationPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type UUID defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class UUIDPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef UUID type;

        eProsima_user_DllExport UUIDPubSubType();

        eProsima_user_DllExport virtual ~UUIDPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };

    /*!
     * @brief This class represents the TopicDataType of the type Assessment defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class AssessmentPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef Assessment type;

        eProsima_user_DllExport AssessmentPubSubType();

        eProsima_user_DllExport virtual ~AssessmentPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };

    /*!
     * @brief This class represents the TopicDataType of the type EventFragment defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class EventFragmentPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef EventFragment type;

        eProsima_user_DllExport EventFragmentPubSubType();

        eProsima_user_DllExport virtual ~EventFragmentPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type EventRecord defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class EventRecordPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef EventRecord type;

        eProsima_user_DllExport EventRecordPubSubType();

        eProsima_user_DllExport virtual ~EventRecordPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };

    /*!
     * @brief This class represents the TopicDataType of the type FragmentAmendmentRequest defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class FragmentAmendmentRequestPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef FragmentAmendmentRequest type;

        eProsima_user_DllExport FragmentAmendmentRequestPubSubType();

        eProsima_user_DllExport virtual ~FragmentAmendmentRequestPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };

    /*!
     * @brief This class represents the TopicDataType of the type Log defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class LogPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef Log type;

        eProsima_user_DllExport LogPubSubType();

        eProsima_user_DllExport virtual ~LogPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type ModuleConfiguration defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class ModuleConfigurationPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef ModuleConfiguration type;

        eProsima_user_DllExport ModuleConfigurationPubSubType();

        eProsima_user_DllExport virtual ~ModuleConfigurationPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type OmittedEvent defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class OmittedEventPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef OmittedEvent type;

        eProsima_user_DllExport OmittedEventPubSubType();

        eProsima_user_DllExport virtual ~OmittedEventPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type Semantic_Version defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class Semantic_VersionPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef Semantic_Version type;

        eProsima_user_DllExport Semantic_VersionPubSubType();

        eProsima_user_DllExport virtual ~Semantic_VersionPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return true;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return true;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            new (memory) Semantic_Version();
            return true;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type OperationalDescription defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class OperationalDescriptionPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef OperationalDescription type;

        eProsima_user_DllExport OperationalDescriptionPubSubType();

        eProsima_user_DllExport virtual ~OperationalDescriptionPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type PhysiologyModification defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class PhysiologyModificationPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef PhysiologyModification type;

        eProsima_user_DllExport PhysiologyModificationPubSubType();

        eProsima_user_DllExport virtual ~PhysiologyModificationPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type PhysiologyValue defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class PhysiologyValuePubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef PhysiologyValue type;

        eProsima_user_DllExport PhysiologyValuePubSubType();

        eProsima_user_DllExport virtual ~PhysiologyValuePubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type PhysiologyWaveform defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class PhysiologyWaveformPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef PhysiologyWaveform type;

        eProsima_user_DllExport PhysiologyWaveformPubSubType();

        eProsima_user_DllExport virtual ~PhysiologyWaveformPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
    /*!
     * @brief This class represents the TopicDataType of the type RenderModification defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class RenderModificationPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef RenderModification type;

        eProsima_user_DllExport RenderModificationPubSubType();

        eProsima_user_DllExport virtual ~RenderModificationPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };

    /*!
     * @brief This class represents the TopicDataType of the type SimulationControl defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class SimulationControlPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef SimulationControl type;

        eProsima_user_DllExport SimulationControlPubSubType();

        eProsima_user_DllExport virtual ~SimulationControlPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };

    /*!
     * @brief This class represents the TopicDataType of the type Status defined by the user in the IDL file.
     * @ingroup AMM_STANDARD
     */
    class StatusPubSubType : public eprosima::fastdds::dds::TopicDataType
    {
    public:

        typedef Status type;

        eProsima_user_DllExport StatusPubSubType();

        eProsima_user_DllExport virtual ~StatusPubSubType() override;

        eProsima_user_DllExport virtual bool serialize(
                void* data,
                eprosima::fastrtps::rtps::SerializedPayload_t* payload) override;

        eProsima_user_DllExport virtual bool deserialize(
                eprosima::fastrtps::rtps::SerializedPayload_t* payload,
                void* data) override;

        eProsima_user_DllExport virtual std::function<uint32_t()> getSerializedSizeProvider(
                void* data) override;

        eProsima_user_DllExport virtual bool getKey(
                void* data,
                eprosima::fastrtps::rtps::InstanceHandle_t* ihandle,
                bool force_md5 = false) override;

        eProsima_user_DllExport virtual void* createData() override;

        eProsima_user_DllExport virtual void deleteData(
                void* data) override;

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED
        eProsima_user_DllExport inline bool is_bounded() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_BOUNDED

    #ifdef TOPIC_DATA_TYPE_API_HAS_IS_PLAIN
        eProsima_user_DllExport inline bool is_plain() const override
        {
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_IS_PLAIN

    #ifdef TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE
        eProsima_user_DllExport inline bool construct_sample(
                void* memory) const override
        {
            (void)memory;
            return false;
        }

    #endif  // TOPIC_DATA_TYPE_API_HAS_CONSTRUCT_SAMPLE

        MD5 m_md5;
        unsigned char* m_keyBuffer;
    };
}

#endif // _FAST_DDS_GENERATED_AMM_AMM_STANDARD_PUBSUBTYPES_H_