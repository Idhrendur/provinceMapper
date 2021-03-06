#ifndef LINK_MAPPING_VERSION_H
#define LINK_MAPPING_VERSION_H
#include "LinkMapping.h"
#include "Parser.h"

class Definitions;
class LinkMappingVersion: commonItems::parser
{
  public:
	LinkMappingVersion(std::istream& theStream,
		 std::string theVersionName,
		 std::shared_ptr<Definitions> theSourceToken,
		 std::shared_ptr<Definitions> theTargetToken,
		 std::string sourceToken,
		 std::string targetToken,
		 int theID);

	LinkMappingVersion(std::string theVersionName,
		 std::shared_ptr<Definitions> sourceDefs,
		 std::shared_ptr<Definitions> targetDefs,
		 std::string theSourceToken,
		 std::string theTargetToken,
		 int theID);

	[[nodiscard]] const auto& getLinks() const { return links; }
	[[nodiscard]] const auto& getName() const { return versionName; }
	[[nodiscard]] auto getID() const { return ID; }
	[[nodiscard]] const auto& getUnmappedSources() const { return unmappedSources; }
	[[nodiscard]] const auto& getUnmappedTargets() const { return unmappedTargets; }
	[[nodiscard]] Mapping isProvinceMapped(int provinceID, bool isSource) const;

	void deactivateLink();
	void activateLinkByIndex(int row);
	void activateLinkByID(int theID);
	void deleteActiveLink();
	void setName(const std::string& theName) { versionName = theName; }
	void setID(int theID) { ID = theID; }
	void copyLinks(const std::shared_ptr<std::vector<std::shared_ptr<LinkMapping>>>& theLinks) const { *links = *theLinks; }
	void moveActiveLinkUp() const;
	void moveActiveLinkDown() const;

	[[nodiscard]] std::optional<int> toggleProvinceByID(int provinceID, bool isSource);
	[[nodiscard]] int addCommentByIndex(const std::string& comment, int index);
	[[nodiscard]] int addRawLink();
	[[nodiscard]] int addRawComment();

	bool operator==(const LinkMappingVersion& rhs) const;

	friend std::ostream& operator<<(std::ostream& output, const LinkMappingVersion& linkMappingVersion);

  private:
	void generateUnmapped() const;
	void removeUnmappedSourceByID(int provinceID) const;
	void removeUnmappedTargetByID(int provinceID) const;
	void addUnmappedSourceByID(int provinceID) const;
	void addUnmappedTargetByID(int provinceID) const;

	int ID = 0;
	std::string versionName;
	int linkCounter = 0;
	int lastActiveLinkIndex = 0;
	std::shared_ptr<Definitions> sourceDefs;
	std::shared_ptr<Definitions> targetDefs;
	std::string sourceToken;
	std::string targetToken;

	std::shared_ptr<LinkMapping> activeLink;

	void registerKeys();
	std::shared_ptr<std::vector<std::shared_ptr<LinkMapping>>> links;
	std::shared_ptr<std::vector<std::shared_ptr<Province>>> unmappedSources;
	std::shared_ptr<std::vector<std::shared_ptr<Province>>> unmappedTargets;
};
std::ostream& operator<<(std::ostream& output, const LinkMappingVersion& linkMappingVersion);

#endif // LINK_MAPPING_VERSION_H