#pragma once

#include "constantpool.h"

namespace jdk {
	/*
	attribute_info{
	 u2 attribute_name_index;
	 u4 attribute_length;
	 u1 attribute[attribute_length];
	}
	*/
	class IAttributeVisit;
	class AttributeInfo:public std::enable_shared_from_this<AttributeInfo>
	{
		friend class AbstractVisit;
	private:
		AttributeInfo(uint16_t i, uint32_t len, const char* b, const uint32_t o, const ConstantPool* cp);
	public:
		QString getAttributeName() const;
		uint32_t getBodyLength() const;
		uint32_t getOffset() const;
		const char* getBody() const;
		void visit(IAttributeVisit&);
		static std::shared_ptr<AttributeInfo> createAttributeInfo(const char* buffer, const uint32_t offset, const ConstantPool* cpool);

		template<typename T>
		void visit(T ft) const;

	protected:
		uint16_t attributeNameIndex;    //�������������������ֵ
		uint32_t length;       // ���ȣ��������ֵ,body_length
		const char* buffer;    //�ļ��Ļ���
		const uint32_t offset;   //nameIndex��ƫ����
		const ConstantPool* cpool;
	};

	class IAttributeVisit {
	public:
		//������Ϊs
		virtual void visit(std::shared_ptr<AttributeInfo>& info) = 0;
	};

	class AbstractVisit:public IAttributeVisit {
	public:
		void visit(std::shared_ptr<AttributeInfo>& info) override;
		virtual void doVisit() = 0;
		QString getAttributeName() const;
		uint32_t getBodyLength();
	private:
		std::shared_ptr<AttributeInfo> info;
		const ConstantPool* cpool;
	};

	template<typename T>
	inline void AttributeInfo::visit(T ft) const
	{
		ft(this->shared_from_this());
	}

}


